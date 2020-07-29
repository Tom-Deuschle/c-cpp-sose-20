#include "atf.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_configuration(int* values, int num_values) {
  for (int i = 0; i < num_values; ++i) {
    printf("%5d", values[i]);
  }
  printf("\n");
}

tp_t create_tp(char* name, int min, int max, constraint_t constraint) {
	tp_t tp;
	tp.name = name;
	tp.min = min;
	tp.max = max;
	tp.constraint = constraint;

	return tp;
}

bool check_constraint(int* values, int num_values, constraint_t constraint) {
	if (!constraint)
		return true;
	
	int p0 = (num_values >= 1) ? values[0] : 0;
	int p1 = (num_values >= 2) ? values[1] : 0;
	int p2 = (num_values >= 3) ? values[2] : 0;
	int p3 = (num_values >= 4) ? values[3] : 0;
	int p4 = (num_values >= 5) ? values[4] : 0;
	int p5 = (num_values >= 6) ? values[5] : 0;
	int p6 = (num_values >= 7) ? values[6] : 0;
	int p7 = (num_values >= 8) ? values[7] : 0;
	int p8 = (num_values >= 9) ? values[8] : 0;
	int p9 = (num_values >= 10) ? values[9] : 0;
	
	return constraint(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

configuration_t* create_config(tp_t* parameters, int* values, int num_parameters) {
	configuration_t* config = (configuration_t *) malloc(sizeof(configuration_t));
	
	tp_t** config_parameters = (tp_t **) malloc(num_parameters * sizeof(tp_t*));
	int* config_values = (int *) malloc(num_parameters * sizeof(int));
	
	for (int i = 0; i < num_parameters; i++) {
		config_parameters[i] = parameters + i;
		config_values[i] = values[i];
	}

	config->parameters = config_parameters;
	config->values = config_values;
	config->size = num_parameters;
	
	return config;
}

void add_config_to_search_space(configuration_t* config, search_space_t* search_space) {
	if (search_space->size == search_space->maxSize) {
		search_space->configurations = realloc(search_space->configurations, 2 * search_space->maxSize * sizeof(configuration_t*));
		search_space->maxSize *= 2;
	}
	
	search_space->configurations[search_space->size] = config;
	search_space->size++;
}

bool process_value(tp_t* parameters, int* values, int num_parameters, int parameter_number, int current_value, search_space_t* search_space) {
	values[parameter_number] = current_value;
	
	if (!check_constraint(values, parameter_number + 1, parameters[parameter_number].constraint))
		return true;
	
	if (parameter_number + 1 == num_parameters) {
		// print_configuration(values, parameter_number + 1);
		configuration_t* config = create_config(parameters, values, num_parameters);
		add_config_to_search_space(config, search_space);
		return true;
	}
	
	return false;
}

void generate_search_space(tp_t* parameters, int num_parameters,
                           search_space_t* search_space) {
					
    search_space->size = 0;
	search_space->maxSize = 4 * num_parameters;
	search_space->configurations = (configuration_t **) malloc(search_space->maxSize * sizeof(configuration_t*));
	
	int* values = (int *) malloc(num_parameters * sizeof(int));

	for (int i = parameters[0].min; i <= parameters[0].max; i++) {
		if (process_value(parameters, values, num_parameters, 0, i, search_space))
			continue;
		
		for (int j = parameters[1].min; j <= parameters[1].max; j++) {
			if (process_value(parameters, values, num_parameters, 1, j, search_space))
				continue;
		
			for (int k = parameters[2].min; k <= parameters[2].max; k++) {
				if (process_value(parameters, values, num_parameters, 2, k, search_space))
					continue;
		
				for (int l = parameters[3].min; l <= parameters[3].max; l++) {
					if (process_value(parameters, values, num_parameters, 3, l, search_space))
						continue;
		
					for (int m = parameters[4].min; m <= parameters[4].max; m++) {
						if (process_value(parameters, values, num_parameters, 4, m, search_space))
							continue;
		
						for (int n = parameters[5].min; n <= parameters[5].max; n++) {
							if (process_value(parameters, values, num_parameters, 5, n, search_space))
								continue;
		
							for (int o = parameters[6].min; o <= parameters[6].max; o++) {
								if (process_value(parameters, values, num_parameters, 6, o, search_space))
									continue;
		
								for (int p = parameters[7].min; p <= parameters[7].max; p++) {
									if (process_value(parameters, values, num_parameters, 7, p, search_space))
										continue;
		
									for (int q = parameters[8].min; q <= parameters[8].max; q++) {
										if (process_value(parameters, values, num_parameters, 8, q, search_space))
											continue;
		
										for (int r = parameters[9].min; r <= parameters[9].max; r++) {
											process_value(parameters, values, num_parameters, 9, r, search_space);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	free(values);
	
}
configuration_t get_config(search_space_t* search_space, int index) {
  return *search_space->configurations[index];
}
void free_search_space(search_space_t* search_space) {
  for (int i = 0; i < search_space->size; i++) {
	  configuration_t* config = search_space->configurations[i];
	  
	  free(config->parameters);
	  free(config->values);
	  free(config);
  }
  
  free(search_space->configurations);
}

int compute_costs(configuration_t* config, cost_function_t cost_function) {
	int* values = config->values;
	int num_values = config->size;
	
	int p0 = (num_values >= 1) ? values[0] : 0;
	int p1 = (num_values >= 2) ? values[1] : 0;
	int p2 = (num_values >= 3) ? values[2] : 0;
	int p3 = (num_values >= 4) ? values[3] : 0;
	int p4 = (num_values >= 5) ? values[4] : 0;
	int p5 = (num_values >= 6) ? values[5] : 0;
	int p6 = (num_values >= 7) ? values[6] : 0;
	int p7 = (num_values >= 8) ? values[7] : 0;
	int p8 = (num_values >= 9) ? values[8] : 0;
	int p9 = (num_values >= 10) ? values[9] : 0;
	
	return cost_function(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

void explore_search_space(search_space_t* search_space, cost_function_t cost_function,
                          SEARCH_STRATEGY search_strategy, ABORT_TYPE abort_type, int abort_value,
                          configuration_t* best_config, int* cost) {
	if (abort_type == EVALUATIONS) {
		for (int i = 0; i < abort_value; i++) {
			
		}
	}
	else {
		if (abort_type == MINUTES)
			abort_value *= 60;
		if (abort_type == HOURS)
			abort_value *= 3600;
		
		time_t start_time = time(NULL);
		time_t end_time = current_time + abort_value;
		
		do {
			
		} while (time(NULL) < end_time);
	}
}
