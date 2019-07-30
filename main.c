#include <stdio.h>
#include <stdlib.h> // atoi() -> string to int
#include <string.h> // strlen() -> string length

typedef struct _ELEMENT
{
    int row;
    int col;
    int value;
} Element;

int n = 0;
int result[1000][1000];
int flag = 0;

FILE *output;

int count_nonzero(int arr[][n]);
void compress(int SparseMatrix[][n], int row, int col, int cnt, Element CompMatrix[]);
void add(int a[][n], int b[][n]);
void multi(int a[][n], int b[][n]);
void trans(int arr[][n]);

int main()
{
    FILE *fp;

    if((fp = fopen("/root/sparse_matrix/hw1_input.txt", "r")) == NULL)
    {
        printf("Failed Open hw1_input.txt\n");
        return 0;
    }

    if((output = fopen("/root/sparse_matrix/hw1_output.txt", "w")) == NULL)
    {
        printf("Failed Opne hw1_output.txt\n");
        return 0;
    }

    char buffer[5]; // parsing the number of matrix
    fgets(buffer, sizeof(buffer), fp);
    n = atoi(buffer);
    printf("%d\n", n);

    int array_A[n][n];
    int array_B[n][n];

    char tmp;
    fscanf(fp, "%c", &tmp);
    printf("%c\n", tmp);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            fscanf(fp, "%d", &array_A[i][j]);
            printf("%d ", array_A[i][j]);
        }
        printf("\n");
    }

    fscanf(fp, "%c%c", &tmp, &tmp);
    printf("%c\n", tmp);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            fscanf(fp, "%d", &array_B[i][j]);
            printf("%d ", array_B[i][j]);
        }
        printf("\n");
    }

    fscanf(fp, " %c ", &tmp);
    printf("%c\n", tmp);

    char m[500];
    fgets(m, sizeof(m), fp);
    printf("%s", m);

    int len = strlen(m);

    for(int i = 0; i < len; i++)
    {
        if(m[i-1] == '+' || m[i-1] == '*' || m[i-1] == "\'")
            fprintf(output, "$\n");

        if(m[i] == '+')
        {
            if(flag == 0)
            {
                if((m[i-1] == 'A' && m[i+1] == 'B') || (m[i-1] == 'B' && m[i+1] == 'A'))
                     add(array_A, array_B);

                else if(m[i-1] == m[i+1])
                {
                    if(m[i-1] == 'A')
                        add(array_A, array_A);

                    else if(m[i-1] == 'B')
                        add(array_B, array_B);
                }
            }

            else if(flag == 1)
            {
                if(m[i+1] == 'A')
                    add(result, array_A);

                else if(m[i+1] == 'B')
                    add(result, array_B);
            }

            flag = 1;
        }

        else if(m[i] == '*')
        {
            if(flag == 0)
            {
                if(m[i-1] == m[i+1])
                {
                    if(m[i-1] == 'A')
                        multi(array_A, array_A);

                    else if(m[i-1] == 'B')
                        multi(array_B, array_B);
                }

                else if(m[i-1] == 'A' && m[i+1] == 'B')
                    multi(array_A, array_B);

                else if(m[i-1] == 'B' && m[i+1] == 'A')
                    multi(array_B, array_A);
            }

            else if(flag == 1)
            {
                if(m[i+1] == 'A')
                    multi(result, array_A);

                else if(m[i+1] == 'B')
                    multi(result, array_B);
            }

            flag = 1;
        }

        else if(m[i] == '\'')
        {
            if(flag == 0 && m[i-1] == 'A')
                trans(array_A);

            else if(flag == 0 && m[i-1] == 'B')
                trans(array_B);

            else if(flag == 1)
                trans(result);
        }

    }

    fclose(fp);
    return 0;
}


int count_nonzero(int arr[][n])
{
    printf("\n[+] CALL : count_nonzero()\n");
    int cnt = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(arr[i][j] != 0)
                cnt++;
        }
    }

    printf("[+] Success Count non-zero\n[+] non-zero : %d\n", cnt);

    if(cnt > (n * n) / 3)
    {
        printf("[!] Dense Matrix\n");
        return 0;
    }

    else
    {
        printf("[!] Sparse Matrix\n");
        return cnt;
    }
}


void compress(int SparseMatrix[][n], int row, int col, int cnt, Element CompMatrix[])
{
    printf("\n[+] CALL : compress()\n");

    int idx = 0;

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(SparseMatrix[i][j] != 0)
            {
                CompMatrix[idx].row = i+1;
                CompMatrix[idx].col = j+1;
                CompMatrix[idx].value = SparseMatrix[i][j];
                idx++;
            }
        }
    }

    printf("[+] Success Compress\n", cnt);

    for(int i = 0; i < cnt; i++)
    {
        printf("%d %d %d\n", CompMatrix[i].row, CompMatrix[i].col, CompMatrix[i].value);
        fprintf(output, "%d %d %d\n", CompMatrix[i].row, CompMatrix[i].col, CompMatrix[i].value);
    }
}

void add(int a[][n], int b[][n])
{
    if(flag == 1)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = result[i][j];
    }

    printf("\n==[+]==\n");
    int add_arr[n][n];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            add_arr[i][j] = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
          add_arr[i][j] = a[i][j] + b[i][j];
          printf("%d ", add_arr[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            result[i][j] = add_arr[i][j];
    }

    int cnt = count_nonzero(add_arr);

    if(cnt != 0)
    {
        fprintf(output, "S\n");
        // memory allocate for sparse matrix
        Element *CompMatrix = (Element*)malloc(sizeof(Element)*(cnt + 1));

        compress(add_arr, n, n, cnt, CompMatrix);

        free(CompMatrix);
    }

    else if(cnt == 0)
    {
        fprintf(output, "D\n");

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                fprintf(output, "%d ", result[i][j]);
            }
            fprintf(output, "\n");
        }
    }
}

void multi(int a[][n], int b[][n])
{
    if(flag == 1)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = result[i][j];
    }

    printf("\n==[*]==\n");
    int multi_arr[n][n];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            multi_arr[i][j] = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                multi_arr[i][j] += a[i][k] * b[k][j];
            }
            printf("%d ", multi_arr[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            result[i][j] = multi_arr[i][j];
    }

    int cnt = count_nonzero(multi_arr);

    if(cnt != 0)
    {
        fprintf(output, "S\n");
        // memory allocate for sparse matrix
        Element *CompMatrix = (Element*)malloc(sizeof(Element)*(cnt + 1));

        compress(multi_arr, n, n, cnt, CompMatrix);

        free(CompMatrix);
    }

    else if(cnt == 0)
    {
        fprintf(output, "D\n");

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                fprintf(output, "%d ", result[i][j]);
            }
            fprintf(output, "\n");
        }
    }
}

void trans(int arr[][n])
{
    if(flag == 1)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                arr[i][j] = result[i][j];
    }

    // transposition (')
    printf("\n==[']==\n");
    int trans_arr[n][n];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            trans_arr[i][j] = arr[i][j];

    for(int i = n-1; i >= 0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            trans_arr[i][j] = arr[j][i];
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", trans_arr[i][j]);
        }
        printf("\n");
    }

    int cnt = count_nonzero(trans_arr);

    if(cnt != 0)
    {
        fprintf(output, "S\n");
        // memory allocate for sparse matrix
        Element *CompMatrix = (Element*)malloc(sizeof(Element)*(cnt + 1));

        compress(trans_arr, n, n, cnt, CompMatrix);

        free(CompMatrix);
    }

    else if(cnt == 0)
    {
        fprintf(output, "D\n");

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                fprintf(output, "%d ", trans_arr[i][j]);
            }
            fprintf(output, "\n");
        }
    }
}
