# 10장 객체지향 프로그래밍 강의내용 정리

---

```cpp
#include <iostream>
using namespace std;
void myswap(int& a, int& b) {  //동일 코드 중복 작성 , 두 함수는 매개 변수만 다르고 나머지 코드는 동일함
int tmp;
tmp = a;
a = b;
b = tmp;
}
void myswap(double & a, double & b) {//동일 코드 중복 작성, 두 함수는 매개 변수만 다르고 나머지 코드는 동일함
double tmp;
tmp = a;
a = b;
b = tmp;
}
int main() {
int a=4, b=5;
myswap(a, b); // myswap(int& a, int& b) 호출
cout << a << '\t' << b << endl;
double c=0.3, d=12.5;
myswap(c, d); // myswap(double& a, double& b) 호출
cout << c << '\t' << d << endl;
}
```

## 제네릭(generic) 또는 일반화

* 함수나 클래스를 일반화시키고, 매개 변수 타입을 지정하여 틀에서 찍어 내듯이 함수나 클래스 코드를 생산하는 기법

## 템플릿

* 함수나 클래스를 일반화하는 C++ 도구
* template 키워드로 함수나 클래스 선언
  - 변수나 매개 변수의 타입만 다르고, 코드 부분이 동일한 함수를 일반화시킴
```cpp
template <class T> 또는
template <typename T>

//3 개의 제네릭 타입을 가진 템플릿 선언
template <class T1, class T2, class T3>
```

![image](https://github.com/user-attachments/assets/ec72f154-e5c6-4e66-9e64-659d2fb72980)

## 구체화(specialization)
* 템플릿의 제네릭 타입에 구체적인 타입 지정(  템플릿 함수로부터 구체화된 함수의 소스 코드 생성 )

![image](https://github.com/user-attachments/assets/52d2f276-fb0d-49e2-a510-22b768da8aef)

![image](https://github.com/user-attachments/assets/337b99d9-be9f-4e01-b3c5-89acda953763)

### 구체화 오류

* 제네릭 타입에 구체적인 타입 지정 시 주의

```cpp
template <class T> void myswap(T & a, T & b) //동일

int s=4;
double t=5;
myswap(s, t);  //매개변수 다름 -> myswap(int &, double &) 함수를 구체화할수 없다
```

### 템플릿 장점
* 함수 코드의 재사용 : 소프트웨어의 생산성과 유용성 높임
### 템플릿 단점
* 포팅에 취약 : 컴파일러에 따라 지원하지 않을 수 있음
* 컴파일 오류 메시지 빈약, 디버깅에 많은 어려움
