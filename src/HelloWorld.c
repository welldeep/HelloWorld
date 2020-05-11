/*
 ============================================================================
 Name        : HelloWorld.c
 Author      : welldeep
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

/**
 * signal sort function
 * @param j1
 * @param j2
 * @return
 */
static int sort_signal_fn (const void *j1, const void *j2)
{
	json_object * const *jso1, * const *jso2,*jso3=NULL,*jso4=NULL;
	int i1, i2;

	jso1 = (json_object* const*)j1;
	jso2 = (json_object* const*)j2;
	if (!*jso1 && !*jso2)
		return 0;
	if (!*jso1)
		return -1;
	if (!*jso2)
		return 1;


	if (!json_object_object_get_ex(*jso1,"signal",&jso3))
	printf("Field %s does not exist\n", "signal");

	if (!json_object_object_get_ex(*jso2,"signal",&jso4))
	printf("Field %s does not exist\n", "signal");


	i1 = json_object_get_int(jso3);
	i2 = json_object_get_int(jso4);

	return -(i1 - i2);
}

/**
 * @brief 
 * 
 * @return int 
 */
int main(void) {
	json_object *ssid_array, *ssid_object;
	int i;

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	ssid_array = json_object_new_array();

	ssid_object = json_object_new_object();
	json_object_object_add(ssid_object,"ssid",json_object_new_string("Flairmicro_XM"));
	json_object_object_add(ssid_object,"signal",json_object_new_int(-35));
	json_object_array_add(ssid_array, ssid_object);
//	json_object_put(ssid_object);

	ssid_object = json_object_new_object();
	json_object_object_add(ssid_object,"ssid",json_object_new_string("and-Business"));
	json_object_object_add(ssid_object,"signal",json_object_new_int(-85));
	json_object_array_add(ssid_array, ssid_object);
//	json_object_put(ssid_object);

	ssid_object = json_object_new_object();
	json_object_object_add(ssid_object,"ssid",json_object_new_string("CMCC-WEB"));
	json_object_object_add(ssid_object,"signal",json_object_new_int(-25));
	json_object_array_add(ssid_array, ssid_object);
//	json_object_put(ssid_object);

	printf("ssid_array=\n");
	for(i=0; i < json_object_array_length(ssid_array); i++)
	{
		json_object *obj = json_object_array_get_idx(ssid_array, i);
		printf("\t[%d]=%s\n", i, json_object_to_json_string(obj));
	}

	json_object_array_sort(ssid_array, sort_signal_fn);

	printf("ssid_array=\n");
	for(i=0; i < json_object_array_length(ssid_array); i++)
	{
		json_object *obj = json_object_array_get_idx(ssid_array, i);
		printf("\t[%d]=%s\n", i, json_object_to_json_string(obj));
	}

	json_object_put(ssid_array);

	return EXIT_SUCCESS;
}
