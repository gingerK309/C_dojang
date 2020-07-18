#include<stdio.h>
#include "parson.h"
#include<stdbool.h>

int main() {
	JSON_Value* rootValue;
	JSON_Object* rootObject;

	//rootValue = json_parse_file("example.json");// JSON 파일 읽어서 파싱
	//rootObject = json_value_get_object(rootValue);// JSON_Value 에서 JSON_Objecrt 를 얻음

	//printf("Title: %s\n", json_object_get_string(rootObject, "Title"));//객체에서 키에 해당하는 문자열을 가져옴
	
	//printf("Year: %d\n", (int)json_object_get_number(rootObject,"year"));//객체에서 키에 해당하는 숫자를 가져옴
	//printf("Runtime: %d\n", (int)json_object_get_number(rootObject, "Runtime"));

	//printf("Genre: %s\n", json_object_get_string(rootObject, "Genre")); 
	//printf("Director: %s\n", json_object_get_string(rootObject, "Director"));

	//printf("Actors:\n");
	//JSON_Array* array = json_object_get_array(rootObject, "Actors"); //객체에서 키에 해당하는 배열을 가져옴
	//for (int i = 0; i < json_array_get_count(array); i++) {
	//	printf("	%s\n", json_array_get_string(array, i));
	//}
	//printf("imdbRating: %f\n", json_object_get_number(rootObject, "imdbRating")); //객체에서 키에 해당하는 숫자를 가져옴
	//printf("KoreaRelease: %d\n", json_object_get_boolean(rootObject, "KoreaRelease"));//객체에서 키에 해당하는 불 값을 가져옴

	//json_value_free(rootValue); //JSON_Value 에 할당된 동적 메모리 해제

	rootValue = json_value_init_object();//JSON_Value 생성 및 초기화
	rootObject = json_value_get_object(rootValue);//JSON_Value에서 JSON_Object를 얻음

	json_object_set_string(rootObject, "Title", "Inception");//객체에 키를 추가하고 문자열 저장
	json_object_set_number(rootObject, "Year", 2010); //객체에 키를 추가하고 숫자 저장
	json_object_set_number(rootObject, "Runtime", 148);
	json_object_set_string(rootObject, "Genre", "Sci-Fi");
	json_object_set_string(rootObject, "Director", "Christopher Nolan");

	json_object_set_value(rootObject, "Actors", json_value_init_array());//객체에 키를 추가하고 배열 생성
	JSON_Array* actors = json_object_get_array(rootObject, "Actors");//객체에서 배열 포인터를 가져옴

	json_array_append_string(actors, "Leonardo DiCaprio");//배열에 문자열 요소 추가
	json_array_append_string(actors, "Joseph Gordon-Levitt");
	json_array_append_string(actors, "Ellen Page");
	json_array_append_string(actors, "Tom Hardy");
	json_array_append_string(actors, "Ken Watanabe");

	json_object_set_number(rootObject, "imdbRating", 8.8);
	json_object_set_boolean(rootObject, "KoreaRelease", true);

	json_serialize_to_file_pretty(rootValue, "output.json"); //JSON_Value를 사람이 읽기 쉬운 문자열로 만든 뒤 파일에 저장
	json_value_free(rootValue);//JSON_Value에 할당된 동적 메모리 해제

	return 0;
	
}