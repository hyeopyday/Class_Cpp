
# 객체지향프로그래밍 요약 (9~13장)

---

## 📚 9장: 가상 함수와 추상 클래스

### ✅ 핵심 개념
- **함수 재정의 vs 오버라이딩**
  - 오버라이딩: `virtual` 키워드로 정의 → 실행 시간에 동적 바인딩
  - 재정의: `virtual` 없이 덮어쓰기 → 정적 바인딩

- **가상 함수 (`virtual`)**
  - 부모 포인터로 자식 객체 접근 시 자식 메서드 호출됨 (다형성 실현)
  - `virtual void f();`

- **가상 소멸자**
  - `virtual ~Base();` 형태로 선언해야 동적 소멸이 제대로 됨

- **추상 클래스**
  - 순수 가상 함수 포함 (`virtual void draw() = 0;`)
  - 객체 생성 불가능, 인터페이스 용도로 사용

---

## 🧬 10장: 템플릿과 STL

### ✅ 템플릿 (제네릭)
- **템플릿 함수**
  ```cpp
  template <class T>
  void myswap(T &a, T &b);
  ```
- **구체화**: 타입 지정 시 자동으로 코드 생성됨

- **템플릿 클래스**
  ```cpp
  template <class T>
  class MyStack {
    ...
  };
  ```

### ✅ STL (Standard Template Library)
- **vector, map, iterator, algorithm**
  ```cpp
  vector<int> v;
  v.push_back(1);
  sort(v.begin(), v.end());
  map<string, string> dic;
  dic["love"] = "사랑";
  ```

- **람다 함수**
  ```cpp
  auto f = [](int x, int y) { return x + y; };
  f(2, 3); // 5
  ```

---

## 📁 11장: 스트림 입출력과 조작자

### ✅ 기본 스트림 객체
- `cin`, `cout`, `cerr`, `clog`

### ✅ 입출력 함수
- `put()`, `get()`, `getline()`, `write()`
- `cin.get()`, `cin.getline()`, `cin.ignore()`

### ✅ 포맷 설정
```cpp
cout.width(10);
cout.fill('*');
cout.precision(3);
```

### ✅ 조작자 사용
```cpp
cout << hex << showbase << 30;
cout << setw(10) << setfill('.') << "Hi";
```

### ✅ 사용자 정의 연산자
```cpp
ostream& operator<<(ostream& out, Point p);
istream& operator>>(istream& in, Point& p);
```

---

## 📄 12장: 파일 입출력 (텍스트 & 바이너리)

### ✅ 파일 스트림 객체
- `ifstream`, `ofstream`, `fstream`

### ✅ 텍스트 I/O
```cpp
ofstream fout("file.txt");
fout << "Hello";

ifstream fin("file.txt");
string s;
fin >> s;
```

- 파일 모드: `ios::in`, `ios::out`, `ios::app`

### ✅ 바이너리 I/O
```cpp
fout.write((char*)buffer, sizeof(buffer));
fin.read((char*)buffer, sizeof(buffer));
```

- 모드: `ios::binary`

### ✅ 임의 접근
```cpp
fin.seekg(0, ios::end);
long size = fin.tellg();
```

---

## 💥 13장: 예외 처리 & extern "C"
  
### ✅ try-catch 구조
```cpp
try {
  if (n == 0) throw "0으로 나눌 수 없음";
} catch (const char* msg) {
  cout << msg;
}
```

### ✅ 사용자 정의 예외 클래스
```cpp
class MyException {
  int line;
  string msg;
};
```

### ✅ 함수 예외 명시
```cpp
int f() throw(int);
```

### ✅ C/C++ 링크 혼합
- C++은 함수 이름이 복잡하게 바뀜 (`name mangling`)
- `extern "C"`를 써야 C에서 컴파일된 함수와 연결 가능

```cpp
extern "C" int f(int x, int y);
```

---

## ✅ 실습 대비
- 다형성, 상속, 예외, 템플릿, 입출력 관련 예제 꼭 복습
- `MyStack`, `Point`, `Shape` 같은 예제는 실습 대비 중요

