#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
/**
	student.c
	C���α׷����⼮������ü����
	@author ��ȭ��
	�й� :201934-364761
*/

/**���� ����ü*/
struct student
{
	/** �̸� */
	char name[20];
	/** �ֹε�Ϲ�ȣ*/
	char idNo[14];
	/**�������_ǥ���*/
	char birthYMD_TXT[20];
	/**�������_���Ŀ�*/
	char birthYMD_sort[8];
	/**���⿩��*/
	char isLeapYear[9];
	/**�������*/
	char hometown[9];
	/**����*/
	char sex[5];
	/** �а� */
	char major[50];
} students[3];

/** �������� �Ǵ��Լ� */
struct student completeStudent(struct student *);
/** ��� �Լ�*/
void printInfo(struct student *);
/** ���� �Լ�*/
void sortInfo(struct student *);

void main() {
	//����_�й�_�̸�
	printf("C���α׷���_201934-364761_��ȭ��\r\n\n");
	//�ȳ����� ���
	printf("\n\n3���� �л� ������ �Է��Ͻÿ�.\r\n");

	//�ݺ��� 3���� �л� 
	for (int i = 0; i < 3; i++) {

		//�л�����ü ����
		struct student std;

		//���м� ���
		printf("------------------------------------------------------------\n");
		//�̸� �Է¹޾� ����ü�� ����
		char name[20];
		printf("�̸� : ");
		strcpy(std.name, gets(name));

		//�а� �Է¹޾� ����ü�� �а��� �Է�
		char major[50];
		printf("�а� : ");
		strcpy(std.major, gets(major));

		//�ֹε�Ϲ�ȣ �Է¹޾� ����ü�� �а��� �Է�
		char idNo[14];
		printf("�ֹε�Ϲ�ȣ : ");
		strcpy(std.idNo, gets(idNo));

		//�Է¹��� �������� �������� ����
		completeStudent(&std);
		
		//�������� ��� �Լ� ȣ��
		printInfo(&std);
		
		//���� �� ����� ���� ����ü �迭�� ����
		students[i] = std;

	}
	//���� �Լ� ȣ��
	sortInfo(students);

	//�ȳ����� ���
	printf("============================================================\n");
	printf("�Է¹��� 3���� ������ ������� �������� ������������ ���\n");
	printf("------------------------------------------------------------\n");

	//���
	for (int j = 0; j < 3; j++) {
		//����Լ� ȣ��
		printInfo(&students[j]);
	}
	printf("\n-----------------------------------\n");

}

/** 
completeStudent
	�Է¹��� ������ ���������� �Ǵ��Ͽ� �Է��ϴ� �Լ� ����
	param : student������
	return student����ü
*/
struct student completeStudent(struct student *stpt)
{
	//�ֹι�ȣ 7��° ����
	char clueNo = (*stpt).idNo[6];

	// ���� �Ǵ�(7��° ���ڰ� ¦���� ����, Ȧ���� ����)
	clueNo % 2 == 0 ? strcpy((*stpt).sex,"����") : strcpy((*stpt).sex,"����");

	// ����� �Ǵ�(�����Ǵ� 7��° ���ڰ� 4���� ũ�� 9���� ������ �ܱ��� �׿ܴ� ���ѹα�)
	 (clueNo > '4' && clueNo < '9') ? strcpy((*stpt).hometown,"�ܱ�") : strcpy((*stpt).hometown,"���ѹα�");

	//���⼳��
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
	//����
	char birthMonth[3] = { (*stpt).idNo[2],(*stpt).idNo[3],'\0' };
	//����
	char birthDate[3] = { (*stpt).idNo[4],(*stpt).idNo[5],'\0' };

	//��¿� ������� ����ü ������ ����
	sprintf((*stpt).birthYMD_TXT,"%s�� %s�� %s��", birthYear ,  birthMonth , birthDate );
	//���Ŀ� ������� ����ü ������ ����
	sprintf((*stpt).birthYMD_sort, "%s%s%s", birthYear, birthMonth, birthDate);


	//�����Ǵ�(100���� ������������ �����鼭 4�� ����������ų� || 400���� ������������ ����)
	if ((atoi(birthYear) % 4 == 0 && atoi(birthYear) % 100 != 0) || atoi(birthYear) % 400 == 0) {
		strcpy((*stpt).isLeapYear, "����");
	}
	else {
		strcpy((*stpt).isLeapYear, "����ƴ�");
	}


	return *stpt;
}

/**
	printInfo
	����ü ��� �Լ�_����ü�� �������� ������ ���
	@param struct student* stpt �л�����ü ������
	*/
void printInfo(struct student* stpt) {
	printf("%s, %s, %s, %s, %s, %s \n", (*stpt).name, (*stpt).birthYMD_TXT, (*stpt).isLeapYear, (*stpt).hometown, (*stpt).sex, (*stpt).major);
}

/**
	sortInfo
	���� �Լ�_����ü �迭�� ������ϱ��� ������������ ����
	@param �л�����ü �迭 ������
*/
void sortInfo(struct student *students) {
	for (int i = 0; i < 2; i++) {
		for (int j = 2; j > i; j--) {
			//��������� ���� ������������ �����Ѵ�.
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
