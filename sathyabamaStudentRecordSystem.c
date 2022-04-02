#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

typedef struct
{
    char username[30];
    char password[20];
} sathyabama_staff_login;

typedef struct
{
    int year;
    int month;
    int days;
} dob;

typedef struct
{
    unsigned int register_id;
    char fatherName[50];
    char studentName[50];
    char studentAddress[300];
    dob studentDob;
} sathyabama_student_info;


void sathyabamaMessageCenter(const char *message)
{
    int len = 0;
    int pos = 0;
    len = (78 - strlen(message)) / 2;
    printf("\t\t\t");
    for (pos = 0; pos < len; pos++)
    {
        printf(" ");
    }
    printf("%s", message);
}
void Message(const char *message)
{
    system("cls");
    printf("\n\t\t\t                  Sathyabama Student Record Management System");
    printf("\n\t\t\t\n");
    sathyabamaMessageCenter(message);
}
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for (index = 0; index < len; ++index)
    {
        if (!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
int IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
int isValidaysate(dob *validaysate)
{
    if (validaysate->year > 9999 ||
        validaysate->year < 1900)
        return 0;
    if (validaysate->month < 1 || validaysate->month > 12)
        return 0;
    if (validaysate->days < 1 || validaysate->days > 31)
        return 0;
    if (validaysate->month == 2)
    {
        if (IsLeapYear(validaysate->year))
            return (validaysate->days <= 29);
        else
            return (validaysate->days <= 28);
    }
    if (validaysate->month == 4 || validaysate->month == 6 ||
        validaysate->month == 9 || validaysate->month == 11)
        return (validaysate->days <= 30);
    return 1;
}
void addStudentInDataBase()
{
    sathyabama_student_info addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen("data.bin", "ab+");
    if (fp == NULL)
    {
        printf("No access to file\n");
        exit(1);
    }
    Message("Add New Students");
    printf("\n\n\t\t\tENTER STUDENT DETAILS BELOW : ");
    printf("\n\t\t\t\n");
    printf("\n\t\t\tRegister No  = ");
    fflush(stdin);
    scanf("%u", &addStudentInfoInDataBase.register_id);

    do
    {
        printf("\n\t\t\tStudent Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentName, 50, stdin);
        status = isNameValid(addStudentInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\tInvalid input");
        }
    } while (!status);

    do
    {
        printf("\n\t\t\tFather Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.fatherName, 50, stdin);
        status = isNameValid(addStudentInfoInDataBase.fatherName);
        if (!status)
        {
            printf("\n\t\t\tInvalid input");
        }
    } while (!status);

    do
    {
        printf("\n\t\t\tStudent Address  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentAddress, 50, stdin);
        status = isNameValid(addStudentInfoInDataBase.studentAddress);
        if (!status)
        {
            printf("\n\t\t\tInvalid input");
        }
    } while (!status);
    do
    {
        printf("\n\t\t\tEnter date of birth : ");
        scanf("%d/%d/%d", &addStudentInfoInDataBase.studentDob.days, &addStudentInfoInDataBase.studentDob.month, &addStudentInfoInDataBase.studentDob.year);
        status = isValidaysate(&addStudentInfoInDataBase.studentDob);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid dob.\n");
        }
    } while (!status);
    fwrite(&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp);
    fclose(fp);
}
void searchStudent()
{
    int found = 0;
    int studentId = 0;
    sathyabama_student_info addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\tNo access to file\n");
        exit(1);
    }
    Message("SEARCH STUDENTS");
    if (fseek(fp, sizeof(sathyabama_staff_login), SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\terror while reading file content\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Student Register No. to search: ");
    fflush(stdin);
    scanf("%u", &studentId);
    while (fread(&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if (addStudentInfoInDataBase.register_id == studentId)
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        printf("\n\t\t\tStudent id = %d\n", addStudentInfoInDataBase.register_id);
        printf("\n\t\t\tStudent name = %s", addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s", addStudentInfoInDataBase.fatherName);
        printf("\n\t\t\tStudent Address = %s", addStudentInfoInDataBase.studentAddress);
        printf("\t\t\tStudent Admission dob =  (%d/%d/%d)", addStudentInfoInDataBase.studentDob.days,
               addStudentInfoInDataBase.studentDob.month, addStudentInfoInDataBase.studentDob.year);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go back to main menu...");
    fflush(stdin);
    getchar();
}
void viewStudent()
{
    int found = 0;
    sathyabama_student_info addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    unsigned int countStudent = 1;
    Message("VIEW STUDENT DETAILS");
    fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        printf("No access to file\n");
        exit(1);
    }
    if (fseek(fp, sizeof(sathyabama_staff_login), SEEK_SET) != 0)
    {
        fclose(fp);
        printf("error while reading file content\n");
        exit(1);
    }
    while (fread(&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tStudent Count = %d\n\n", countStudent);
        printf("\t\t\tStudent Register No. = %u\n", addStudentInfoInDataBase.register_id);
        printf("\t\t\tStudent Name = %s", addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s", addStudentInfoInDataBase.fatherName);
        printf("\t\t\tStudent Address = %s", addStudentInfoInDataBase.studentAddress);
        printf("\t\t\tStudent Dob =  (%d/%d/%d)\n\n", addStudentInfoInDataBase.studentDob.days,
               addStudentInfoInDataBase.studentDob.month, addStudentInfoInDataBase.studentDob.year);
        found = 1;
        ++countStudent;
    }
    fclose(fp);
    if (!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go back to main menu...");
    fflush(stdin);
    getchar();
}
void deleteStudent()
{
    int found = 0;
    int studentDelete = 0;
    sathyabama_staff_login fileHeaderInfo = {0};
    sathyabama_student_info addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    Message("Delete Student Details");
    fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        printf("No access to file\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin", "wb");
    if (tmpFp == NULL)
    {
        fclose(fp);
        printf("No access to file\n");
        exit(1);
    }
    fread(&fileHeaderInfo, sizeof(sathyabama_staff_login), 1, fp);
    fwrite(&fileHeaderInfo, sizeof(sathyabama_staff_login), 1, tmpFp);
    printf("\n\t\t\tEnter Student Register No. for deletion: ");
    scanf("%d", &studentDelete);
    while (fread(&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if (addStudentInfoInDataBase.register_id != studentDelete)
        {
            fwrite(&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found) ? printf("\n\t\t\tRecord deleted successfully...") : printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove("data.bin");
    rename("tmp.bin", "data.bin");
}
void updateCredential(void)
{
    sathyabama_staff_login fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[30] = {0};
    unsigned char password[20] = {0};
    Message("update Credential");
    fp = fopen("data.bin", "rb+");
    if (fp == NULL)
    {
        printf("No access to file\n");
        exit(1);
    }
    fread(&fileHeaderInfo, sizeof(sathyabama_staff_login), 1, fp);
    if (fseek(fp, 0, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName, 30, stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password, 20, stdin);
    strncpy(fileHeaderInfo.username, userName, sizeof(userName));
    strncpy(fileHeaderInfo.password, password, sizeof(password));
    fwrite(&fileHeaderInfo, sizeof(sathyabama_staff_login), 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
void menu()
{
    int choice = 0;
    do
    {
        Message("MAIN MENU");
        printf("\n\n\n\t\t\t1. Add Student");
        printf("\n\t\t\t2. Search Student");
        printf("\n\t\t\t3. View Student");
        printf("\n\t\t\t4. Delete Student");
        printf("\n\t\t\t5. update Password");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addStudentInDataBase();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            viewStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you for using sathyabama student record system!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tInvalid input!");
        }
    } while (choice != 0);
}
void login()
{
    system("cls");
    unsigned char userName[30] = {0};
    unsigned char password[20] = {0};
    int L = 0;
    sathyabama_staff_login fileHeaderInfo = {0};
    FILE *fp = NULL;
    Message("Sathyabama Staff Login");
    fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        printf("No access to file\n");
        exit(1);
    }
    fread(&fileHeaderInfo, sizeof(sathyabama_staff_login), 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername: ");
        fgets(userName, 30, stdin);
        printf("\n\t\t\t\tPassword: ");
        fgets(password, 20, stdin);
        if ((!strcmp(userName, fileHeaderInfo.username)) && (!strcmp(password, fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Plese Check Your Password and Username Again.\n\n");
            L++;
        }
    } while (L <= 3);
    if (L > 3)
    {
        Message("Login Failed");
        printf("\t\t\t\tUnknown User.");
        getch();
        system("cls");
    }
}
int isFileExists(const char *path)
{
    FILE *fp = fopen(path, "rb");
    int status = 0;
    if (fp != NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}
void runner()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] = "Techzamia\n";
    const char defaultPassword[] = "Sathyabama\n";
    sathyabama_staff_login fileHeaderInfo = {0};
    status = isFileExists("data.bin");
    if (!status)
    {
        fp = fopen("data.bin", "wb");
        if (fp != NULL)
        {
            strncpy(fileHeaderInfo.password, defaultPassword, sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username, defaultUsername, sizeof(defaultUsername));
            fwrite(&fileHeaderInfo, sizeof(sathyabama_staff_login), 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    runner();
    login();
    return 0;
}