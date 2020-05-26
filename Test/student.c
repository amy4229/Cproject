#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
/**
	student.c
	C프로그래밍출석수업대체과제
	@author 김화선
	학번 :201934-364761
*/

/**힉생 구조체*/
struct student
{
	/** 이름 */
	char name[20];
	/** 주민등록번호*/
	char idNo[14];
	/**생년월일_표기용*/
	char birthYMD_TXT[20];
	/**생년월일_정렬용*/
	char birthYMD_sort[8];
	/**윤년여부*/
	char isLeapYear[9];
	/**출생지역*/
	char hometown[9];
	/**성별*/
	char sex[5];
	/** 학과 */
	char major[50];
} students[3];

/** 인적사항 판단함수 */
struct student completeStudent(struct student *);
/** 출력 함수*/
void printInfo(struct student *);
/** 정렬 함수*/
void sortInfo(struct student *);

void main() {
	//과제_학번_이름
	printf("C프로그래밍_201934-364761_김화선\r\n\n");
	//안내문구 출력
	printf("\n\n3명의 학생 정보를 입력하시오.\r\n");

	//반복문 3명의 학생 
	for (int i = 0; i < 3; i++) {

		//학생구조체 선언
		struct student std;

		//구분선 출력
		printf("------------------------------------------------------------\n");
		//이름 입력받아 구조체에 설정
		char name[20];
		printf("이름 : ");
		strcpy(std.name, gets(name));

		//학과 입력받아 구조체의 학과에 입력
		char major[50];
		printf("학과 : ");
		strcpy(std.major, gets(major));

		//주민등록번호 입력받아 구조체의 학과에 입력
		char idNo[14];
		printf("주민등록번호 : ");
		strcpy(std.idNo, gets(idNo));

		//입력받은 정보외의 인적사항 설정
		completeStudent(&std);
		
		//인적사항 출력 함수 호출
		printInfo(&std);
		
		//정렬 및 출력을 위한 구조체 배열에 복사
		students[i] = std;

	}
	//정렬 함수 호출
	sortInfo(students);

	//안내문구 출력
	printf("============================================================\n");
	printf("입력받은 3명의 정보를 생년월일 기준으로 오름차순으로 출력\n");
	printf("------------------------------------------------------------\n");

	//출력
	for (int j = 0; j < 3; j++) {
		//출력함수 호출
		printInfo(&students[j]);
	}
	printf("\n-----------------------------------\n");

}

/** 
completeStudent
	입력받은 정보로 인적사항을 판단하여 입력하는 함수 정의
	param : student포인터
	return student구조체
*/
struct student completeStudent(struct student *stpt)
{
	//주민번호 7번째 숫자
	char clueNo = (*stpt).idNo[6];

	// 성별 판단(7번째 숫자가 짝수면 여자, 홀수는 남자)
	clueNo % 2 == 0 ? strcpy((*stpt).sex,"여자") : strcpy((*stpt).sex,"남자");

	// 출생지 판단(국적판단 7번째 숫자가 4보다 크고 9보다 작으면 외국인 그외는 대한민국)
	 (clueNo > '4' && clueNo < '9') ? strcpy((*stpt).hometown,"외국") : strcpy((*stpt).hometown,"대한민국");

	//생년설정
	char birthYear[5];
	switch (clueNo) {
	case '1': case '2': case '5': case '6':
		birthYear[0] = '1';
		birthYear[1] = '9';
		break;
	case '3': case '4': case '7': case '8':
		birthYear[0] = '2';
		birthYear[1] = '0';
		break;
	case '9': case '10' :
		birthYear[0] = '1';
		birthYear[1] = '8';
		break;
	}
	birthYear[2] = (*stpt).idNo[0];
	birthYear[3] = (*stpt).idNo[1];
	birthYear[4] = '\0';
	//생월
	char birthMonth[3] = { (*stpt).idNo[2],(*stpt).idNo[3],'\0' };
	//생일
	char birthDate[3] = { (*stpt).idNo[4],(*stpt).idNo[5],'\0' };

	//출력용 생년월일 구조체 변수에 설정
	sprintf((*stpt).birthYMD_TXT,"%s년 %s월 %s일", birthYear ,  birthMonth , birthDate );
	//정렬용 생년월일 구조체 변수에 설정
	sprintf((*stpt).birthYMD_sort, "%s%s%s", birthYear, birthMonth, birthDate);


	//윤년판단(100으로 나눠떨어지지 않으면서 4로 나누어떨어지거나 || 400으로 나눠떨어지면 윤년)
	if ((atoi(birthYear) % 4 == 0 && atoi(birthYear) % 100 != 0) || atoi(birthYear) % 400 == 0) {
		strcpy((*stpt).isLeapYear, "윤년");
	}
	else {
		strcpy((*stpt).isLeapYear, "윤년아님");
	}


	return *stpt;
}

/**
	printInfo
	구조체 출력 함수_구조체를 포맷으로 편집해 출력
	@param struct student* stpt 학생구조체 포인터
	*/
void printInfo(struct student* stpt) {
	printf("%s, %s, %s, %s, %s, %s \n", (*stpt).name, (*stpt).birthYMD_TXT, (*stpt).isLeapYear, (*stpt).hometown, (*stpt).sex, (*stpt).major);
}

/**
	sortInfo
	정렬 함수_구조체 배열을 생년월일기준 오름차순으로 정렬
	@param 학생구조체 배열 포인터
*/
void sortInfo(struct student *students) {
	for (int i = 0; i < 2; i++) {
		for (int j = 2; j > i; j--) {
			//생년월일을 비교후 오름차순으로 정렬한다.
			struct student  student1= *(students + i);
			struct student student2 = *(students + j );
			if (atoi(student1.birthYMD_sort)> atoi(student2.birthYMD_sort)) {
				struct student temp = student1;
				*(students + i) = student2;
				*(students + j) = temp;
			}
		}
	}
};
