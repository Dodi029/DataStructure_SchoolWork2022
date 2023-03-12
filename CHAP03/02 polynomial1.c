#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))		// 왼쪽은 참, 오른쪽은 거짓임을 뜻함 (조건연산자)
											// 전처리지시자로 미리 만들어놓으면 빠르게 사용가능
#define MAX_DEGREE 101
typedef struct { 			// 다항식 구조체 타입 선언
	int degree;			// 다항식의 차수
	float coef[MAX_DEGREE];	// 다항식의 계수
} polynomial;

// C = A+B 여기서 A와 B는 다항식이다. 구조체가 반환된다. 
polynomial poly_add1(polynomial A, polynomial B)
{
	polynomial C;				// 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0;	// 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수 // 차수 비교 -> 더 큰 차수를 C.degree에 넣음 -> 최고차항이 5이므로 5가 들어감

	while (Apos <= A.degree && Bpos <= B.degree) {		// A.degree =5, B.degree = 4
		if (degree_a > degree_b) {  // A항 > B항		//A항 차수가 클 떄 실행
			C.coef[Cpos++] = A.coef[Apos++];		// 코드 실행 후 Cpos값 증가, 선 실행 후 증가
			degree_a--;		// 단독으로 쓰임 = a감 감소
		}
		else if (degree_a == degree_b) {  // A항 == B항		// 차수가 같을 떄 실행
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {			// B항 > A항		// B항 차수가 클 떄 실행
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;		
}

void print_poly(polynomial p)
{
	for (int i = p.degree; i>0; i--)
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	printf("%3.1f \n", p.coef[p.degree]);
}

// 주함수
int main(void)
{
	polynomial a = { 5,{ 3, 6, 0, 0, 0, 10 } };
	polynomial b = { 4,{ 7, 0, 5, 0, 1 } };
	polynomial c;

	print_poly(a);		// 실수로 출력
	print_poly(b);		// 실수로 출력
	c = poly_add1(a, b);
	printf("---------------------------------------------------------------------------- - \n");
	print_poly(c);		// 
	return 0;
}