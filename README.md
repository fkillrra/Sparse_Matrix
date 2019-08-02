# Sparse Matrix

**Sparse Matrix** is a matrix in which most of the elements are zero.

![1564570830710](https://user-images.githubusercontent.com/32171039/62322993-4765b580-b4e1-11e9-93ab-a89ca54bbf30.png)

---

### Usage
> ./SparseMatrix hw1_input.txt hw1_output.txt

---

### info function

```c
int count_nonzero(int arr[][n])
```

int 형의 return 값을 반환하며, 반환값은 행렬에서 0이 아닌 요소값의 개수입니다.
해당 함수를 호출 할 때 결과가 저장된 2차원 배열을 인자로 주고, 반복문을 통해 해당 배열의 값이 0인지를 검사하여 0이 아닌 값이 존재할 때 지역으로 선언한 cnt 변수에 +1 하여 검사가 끝나고, 최종적으로 도출된 cnt 값을 반환합니다.



```c
void compress(int SparseMatrix[][n], int row, int col, int cnt, Element CompMatrix[])
```

compress() 함수는 반환값이 존재하지 않는 함수로 희소 행렬임이 판단되었을 때 호출되어 재정렬한 뒤 hw1_output.txt 파일에 값을 쓰는 역할을 합니다.

함수가 호출될 때 희소 행렬로 판단되는 행렬과 해당 행렬의 행(row), 열(col), 0이 아닌 수의 개수(cnt), 구조체 Element 배열이 인자값으로 들어가게 되고, 반복문을 통해 재정렬 및 hw1_output.txt 파일에 재정렬된 값을 씁니다.



```c
void add(int a[][n], int b[][n])
```

add() 함수에서는 행렬 A와 B를 받아 더하기 연산을 합니다.
또한 연산 결과를 전역으로 선언된 result 배열에 반복문을 통해 값 복사를 하고, hw1_output.txt 파일에 쓰기를 진행합니다.



```c
void multi(int a[][n], int b[][n])
```

multi() 함수에서는 행렬 A와 B를 받아 곱하기 연산을 합니다.
또한 add() 함수와 동일하게 연산 결과를 전역으로 선언된 result 배열에 반복문을 통해 값 복사를 하며, hw1_output.txt 파일에 쓰기를 진행합니다.



```c
void trans(int arr[][n])
```


trans() 함수는 하나의 행렬을 받아 반복문을 통해 270도 회전시키며 결과를 전역으로 선언된 result 배열 및 hw1_output.txt 파일에 저장합니다.

---

### Process

![1564687184618](https://user-images.githubusercontent.com/32171039/62323049-6106fd00-b4e1-11e9-8630-e20ed2c30a3d.png)

기본적으로 input 파일과 output 파일이 존재하는지 유무를 확인하고, 없다면 예외처리를 통해 프로그램이 정상적으로 동작할 수 있도록 했습니다.

input 파일이 존재한다면 파일의 값을 파싱하여 array_A와 array_B에 저장하고, 수식에 맞게 연산을 하며 Sparse, Dense를 판단하여 Sparse Matrix일 때 Compress하여 output 파일에 값을 쓰고 프로그램은 종료됩니다.

이때 Sparse / Dense의 여부는 count_nonzero() 함수를 통해 행렬의 요소 중 0이 1/3을 초과하는지 확인하였는데, Dense일 때 반환값을 0으로, Sparse일 때 반환값을 non-zero의 값으로 세팅하여 각 연산 함수에서 이를 이용하여 반환값이 0이 아닐때 (Sparse일 때) compress() 함수를 호출하여 재정렬 및 hw1_output.txt 파일에 쓰기 작업을 하였습니다.
