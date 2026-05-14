#include <stdio.h>

typedef struct
{
    int id;
    char name[30];
    float marks;
} Student;

/* Function Prototypes */
void store_records(const char *filename, int n);
int create_seek_positions(const char *filename, long positions[]);
void display_record(const char *filename, long position);

int main()
{
    int n, choice;
    long positions[100];

    printf("Enter number of records: ");
    scanf("%d", &n);

    store_records("student.txt", n);

    /* Create array of seek positions */
    int total = create_seek_positions("student.txt", positions);

    printf("\nStored Positions:\n");

    for(int i = 0; i < total; i++)
    {
        printf("Record %d -> Position %ld\n", i + 1, positions[i]);
    }

    printf("\nEnter record number to display: ");
    scanf("%d", &choice);

    if(choice >= 1 && choice <= total)
    {
        display_record("student.txt", positions[choice - 1]);
    }
    else
    {
        printf("Invalid record number\n");
    }

    return 0;
}

/* Function to store records in ASCII file */
void store_records(const char *filename, int n)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "w");

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
        scanf("%29s", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        fprintf(fp, "%d %s %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

/* Function to create seek positions */
int create_seek_positions(const char *filename, long positions[])
{
    FILE *fp;
    Student s;
    int count = 0;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }

    while(1)
    {
        positions[count] = ftell(fp);

        if(fscanf(fp, "%d %s %f",
                  &s.id, s.name, &s.marks) == EOF)
        {
            break;
        }

        count++;
    }

    fclose(fp);

    return count;
}

/* Function to display record using seek position */
void display_record(const char *filename, long position)
{
    FILE *fp;
    Student s;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fseek(fp, position, SEEK_SET);

    fscanf(fp, "%d %s %f",
           &s.id, s.name, &s.marks);

    printf("\nRecord Found:\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Marks: %.2f\n", s.marks);

    fclose(fp);
}