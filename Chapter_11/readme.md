# 📘 C++ 템플릿과 제네릭 프로그래밍 요약

## 1. 학습 목표

- 일반화(제네릭)와 템플릿의 개념과 목적 이해  
- 템플릿으로부터 구체화(Specialization) 과정 이해  
- 템플릿 함수 및 클래스 작성과 활용  
- STL(Standard Template Library) 이해 및 활용  
- `vector`, `map` 등의 STL 컨테이너 사용법  
- `iterator`와 알고리즘 함수 이해 및 활용  
- `auto` 키워드 사용법  
- 람다식(Lambda Expression)의 개념 및 작성과 호출

---

## 2. 함수 중복 문제

```cpp
void myswap(int& a, int& b);
void myswap(double& a, double& b);
```

- 매개변수 타입만 다르고 코드 내용은 동일 → **코드 중복 발생**

---

## 3. 일반화와 템플릿

### ✅ 템플릿이란?
- **일반화(generic)** 기법을 C++에서 구현한 도구
- 함수나 클래스에서 타입을 매개변수화하여 **중복을 제거**
- `template <class T>` 또는 `template <typename T>` 사용

### ✅ 템플릿 함수 예시

```cpp
template <class T>
void myswap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
```

---

## 4. 템플릿의 구체화 (Specialization)

- 템플릿을 사용할 때, 컴파일러는 **필요한 타입으로 실제 함수를 생성**  
- 예시:

```cpp
int a = 4, b = 5;
myswap(a, b); // T -> int

double x = 1.2, y = 3.4;
myswap(x, y); // T -> double
```

---

## 5. 템플릿 클래스

```cpp
template <typename T>
class MyArray {
private:
    T arr[100];
    int size;
public:
    void add(T value);
    T get(int index);
};
```

---

## 6. STL (Standard Template Library)

- **컨테이너**: 데이터를 담는 객체 (`vector`, `list`, `map` 등)  
- **이터레이터**: 컨테이너 내부를 순회하는 포인터 같은 개념  
- **알고리즘**: 정렬, 탐색 등 (`sort()`, `find()` 등)

### ✅ vector 예시

```cpp
#include <vector>
#include <algorithm>

std::vector<int> v = {5, 3, 8, 1};
std::sort(v.begin(), v.end());
```

---

## 7. auto 키워드

- 변수의 타입을 컴파일러가 자동 추론

```cpp
auto x = 10;        // int
auto y = 3.14;      // double
auto it = v.begin(); // vector<int>::iterator
```

---

## 8. 람다식 (Lambda Expression)

- **이름 없는 함수**를 한 줄로 정의
- `[]`로 시작하며, 파라미터와 실행문 포함

```cpp
auto add = [](int a, int b) {
    return a + b;
};

int result = add(3, 5); // result = 8
```

### ✅ STL + 람다 예시

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};

std::for_each(v.begin(), v.end(), [](int x) {
    std::cout << x << " ";
});
```

---

## ✅ 요약

C++ 템플릿은 **코드 중복을 제거하고**, 다양한 타입에 대해 유연한 프로그래밍을 가능하게 함.  
STL과 결합하면 훨씬 강력하고 간결한 코드 작성을 도와줌.


