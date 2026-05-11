#include <stdio.h>

typedef struct
{
    int id;
    char name[30];
    float marks;
} Student;

/* Function Prototypes */
void store_records(const char *filename, int n);
void display_mth_record(const char *filename, int m);
void delete_record(const char *filename, int record_no);
void display_all(const char *filename);

int main()
{
    int n, m, del;

    printf("Enter number of records: ");
    scanf("%d", &n);

    store_records("student.dat", n);

    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    display_mth_record("student.dat", m);

    printf("\nEnter record number to delete: ");
    scanf("%d", &del);

    delete_record("student.dat", del);

    printf("\nRecords after deletion:\n");
    display_all("student.dat");

    return 0;
}

/* Function to store records in binary file */
void store_records(const char *filename, int n)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "wb");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for(int i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf(" %29[^\n]", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

/* Function to display m-th record using fseek */
void display_mth_record(const char *filename, int m)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    if(m <= 0)
    {
    printf("Invalid record number\n");
    fclose(fp);
    return;
    }

    /* Move file pointer to m-th record */
    fseek(fp, (m - 1) * sizeof(Student), SEEK_SET);

    if(fread(&s, sizeof(Student), 1, fp) == 1)
    {
        printf("\nRecord %d:\n", m);
        printf("ID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    }
    else
    {
        printf("Record not found\n");
    }

    fclose(fp);
}

/* Function to delete a record */
void delete_record(const char *filename, int record_no)
{
    FILE *fp, *temp;
    Student s;
    int count = 1;

    fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if(temp == NULL)
    {
        printf("Error creating temp file\n");
        fclose(fp);
        return;
    }

    while(fread(&s, sizeof(Student), 1, fp) == 1)
    {
        if(count != record_no)
        {
            fwrite(&s, sizeof(Student), 1, temp);
        }

        count++;
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.dat", filename);

    printf("Record deleted successfully\n");
}

/* Function to display all records */
void display_all(const char *filename)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    while(fread(&s, sizeof(Student), 1, fp) == 1)
    {
        printf("\nID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    }

    fclose(fp);
}