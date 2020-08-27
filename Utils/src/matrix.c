#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <general_logs.h>
#include <garbage_collector.h>
#include <common_structures.h>
#include "../include/matrix.h"

void add_row(t_matrix* self){
    self -> amount_of_rows++;
    self -> data = realloc(self -> data, self -> amount_of_rows * sizeof(void**)); // Resigno espacio para una fila más
    (self -> data)[self -> amount_of_rows - 1] = calloc(self -> amount_of_columns, sizeof(void*)); // Asigno espacio para las columnas de esa fila
}

void add_column(t_matrix* self){
    self -> amount_of_columns++;

    //A cada fila, le reasigno espacio considerando que ahora tienen una columna más
    //A su vez, designo nuevo espacio de memoria para la cantidad actual de columnas
    //Muevo los punteros de lugar y libero el espacio de la columna vieja
    for(uint32_t row_index = 1; row_index <= self -> amount_of_rows; row_index++){
        void** old_column = (self -> data)[row_index - 1];
        (self -> data)[row_index - 1] = calloc(self -> amount_of_columns, sizeof(void*));

        for(uint32_t column_index = 1; column_index <= (self -> amount_of_columns) - 1; column_index++){
            void* element = old_column[column_index - 1];
            matrix_insert_element_at(self, element, row_index, column_index);
        }
        free(old_column);
    }
}

void expand(t_matrix* self, uint32_t row_index, uint32_t column_index){

    if(self -> must_be_square){
        uint32_t size = row_index > column_index ? row_index : column_index;

        while (self -> amount_of_rows < size){
            add_row(self);
        }
        while (self -> amount_of_columns < size){
            add_column(self);
        }
    }
    else{
        while(self -> amount_of_rows < row_index){
            add_row(self);
        }

        while (self -> amount_of_columns < column_index){
            add_column(self);
        }
    }
}

void consider_expanding(t_matrix* self, uint32_t row_index, uint32_t column_index){

    if (row_index > self -> amount_of_rows || column_index > self -> amount_of_columns){
        if (self -> is_expandable){
            expand(self, row_index, column_index);
        }
        else{
            log_expanding_unexpandable_matrix_error();
            free_system();
        }
    }
}

void assert_strictly_positive_indexes(uint32_t row_index, uint32_t column_index){

    if(row_index <= 0 || column_index <= 0){
        log_invalid_index_error();
        free_system();
    }
}

t_matrix* matrix_create(uint32_t amount_of_rows, uint32_t amount_of_columns, bool should_be_expandable, bool should_be_squared){

    assert_strictly_positive_indexes(amount_of_rows, amount_of_columns);

    if(should_be_squared && amount_of_rows != amount_of_columns){
        log_are_not_equals_columns_and_rows_in_squared_matrix_error();
        free_system();
    }

    t_matrix* matrix = safe_malloc(sizeof(t_matrix));
    matrix -> amount_of_rows = amount_of_rows;
    matrix -> amount_of_columns = amount_of_columns;

    matrix -> data = safe_malloc(amount_of_rows * sizeof(void**));
    for(uint32_t row_index = 0; row_index < matrix -> amount_of_rows; row_index++){
        (matrix -> data)[row_index] = calloc(amount_of_columns, sizeof(void*));
    }

    matrix -> must_be_square = should_be_squared;
    matrix -> is_expandable = should_be_expandable;
    return matrix;
}

t_matrix* matrix_create_of_size(uint32_t matrix_size, bool should_be_expandable, bool should_be_squared){
    return matrix_create(matrix_size, matrix_size, should_be_expandable, should_be_squared);
}

void matrix_insert_element_at(t_matrix* self, void* element, uint32_t row_index, uint32_t column_index){

    assert_strictly_positive_indexes(row_index, column_index);

    consider_expanding(self, row_index, column_index);
    (self -> data)[row_index - 1][column_index - 1] = element;
}

void* matrix_element_at(t_matrix* self, uint32_t row_index, uint32_t column_index){

    assert_strictly_positive_indexes(row_index, column_index);

    if(self -> amount_of_rows < row_index || self -> amount_of_columns < column_index){
        log_invalid_positions_error();
        free_system();
    }
    return (self -> data)[row_index - 1][column_index - 1];
}

void* matrix_remove_element_at(t_matrix* self, uint32_t row_index, uint32_t column_index){
    void* matrix_element = matrix_element_at(self, row_index, column_index);
    matrix_insert_element_at(self, NULL, row_index, column_index);
    return matrix_element;
}

void matrix_iterate_doing(t_matrix* self, void (*closure) (void*)){

    for(uint32_t row_index = 1; row_index <= self -> amount_of_rows; row_index++){
        for(uint32_t column_index = 1; column_index <= self -> amount_of_columns; column_index++){
            void* matrix_element = matrix_element_at(self, row_index, column_index);
            (*closure) (matrix_element);
        }
    }
}

void print_matrix(t_matrix* self, void (*matrix_element_printer) (void*)){
    for(uint32_t row_number = 1; row_number <= self -> amount_of_rows; row_number++){
        for(uint32_t column_number = 1; column_number <= self -> amount_of_columns; column_number++) {
            void* matrix_element = matrix_element_at(self, row_number, column_number);
            if(matrix_element != NULL){
                (*matrix_element_printer) (matrix_element);
            }
            else{
                printf("%10s", "Empty");
            }
        }
        printf("\n");
    }
}

void matrix_destroy(t_matrix* self){

    for(uint32_t row_index = 0; row_index < self -> amount_of_rows; row_index++){
        free((self -> data)[row_index]);
    }
    free(self -> data);
    free(self);
}

void matrix_destroy_and_destroy_elements(t_matrix* self, void (*data_destroyer) (void*)){
    matrix_iterate_doing(self, data_destroyer);
    matrix_destroy(self);
}