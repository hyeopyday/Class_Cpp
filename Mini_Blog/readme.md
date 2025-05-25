# 미니 블로그 v1.0 개발 보고서

## 1. 프로그램 개요

### 1.1 과제 목표
사용자가 짧은 글을 작성하여 저장하고 목록을 보거나 특정 글을 자세히 볼 수 있는 간단한 블로그 시스템을 C++로 구현

### 1.2 개발 환경
- **언어**: C++
- **컴파일러**: C++11 이상 지원 컴파일러
- **사용 라이브러리**: 표준 라이브러리 (iostream, vector, string, ctime 등)

### 1.3 주요 기능
1. 새 글 쓰기 (제목, 내용, 작성자 입력)
2. 글 목록 보기 (간단한 정보 표시)
3. 글 읽기 (상세 내용 표시)
4. 글 삭제 (확인 후 삭제)

## 2. 프로그램 설계

### 2.1 파일 구조
프로젝트는 객체지향 설계 원칙에 따라 다음과 같이 분리되었습니다:

```
미니블로그_프로젝트/
├── Post.h              # Post 클래스 선언
├── Post.cpp            # Post 클래스 구현
├── BlogManager.h       # BlogManager 클래스 선언
├── BlogManager.cpp     # BlogManager 클래스 구현
├── main.cpp            # 메인 함수
└── Makefile           # 컴파일 자동화
```

### 2.2 클래스 설계

#### Post 클래스 (Post.h/Post.cpp)
```cpp
class Post {
private:
    string title;       // 게시물 제목
    string content;     // 게시물 내용
    string author;      // 작성자
    string date;        // 작성 날짜
    
public:
    // 생성자, Getter/Setter 함수들
    // 출력 관련 함수들
};
```

**설계 특징:**
- **캡슐화**: private 멤버 변수로 데이터 보호
- **자동 날짜 설정**: 생성 시 현재 시간 자동 기록
- **다양한 출력 형태**: 요약 보기와 상세 보기 분리

#### BlogManager 클래스 (BlogManager.h/BlogManager.cpp)
```cpp
class BlogManager {
private:
    vector<Post> posts;     // 모든 게시물 저장
    
public:
    // 각종 기능 함수들
    void run();            // 메인 실행 루프
};
```

**파일 분리의 장점:**
- **헤더 가드**: `#ifndef`를 사용한 중복 포함 방지
- **컴파일 효율성**: 수정된 파일만 재컴파일
- **코드 가독성**: 선언과 구현의 명확한 분리
- **유지보수성**: 각 클래스별 독립적 관리

**설계 특징:**
- **단일 책임 원칙**: 블로그 관리만 담당
- **사용자 인터페이스**: 메뉴 기반 대화형 인터페이스
- **예외 처리**: 잘못된 입력에 대한 안전한 처리

### 2.2 데이터 구조
- **저장 방식**: `vector<Post>` 사용으로 동적 크기 조절
- **인덱스 기반**: 0부터 시작하는 인덱스로 게시물 관리
- **메모리 관리**: 자동 메모리 관리 (스마트 포인터 불필요)

## 3. 주요 코드 설명

### 3.1 Post 클래스 핵심 기능

#### 생성자 및 날짜 설정
```cpp
Post(const string& postTitle, const string& postContent, const string& postAuthor) 
    : title(postTitle), content(postContent), author(postAuthor) {
    setCurrentDate();
}

void setCurrentDate() {
    time_t now = time(0);
    char* timeStr = ctime(&now);
    date = string(timeStr);
    // 개행 문자 제거
    if (!date.empty() && date[date.length()-1] == '\n') {
        date.erase(date.length()-1);
    }
}
```
- **멤버 초기화 리스트** 사용으로 효율적인 초기화
- **ctime 라이브러리** 활용한 현재 시간 자동 설정

#### 출력 함수들
```cpp
void displaySummary(int index) const {
    cout << "[" << index << "] " << title 
         << " | 작성자: " << author 
         << " | 날짜: " << date << endl;
}

void displayFull() const {
    cout << "\n=== 게시물 상세 보기 ===" << endl;
    cout << "제목: " << title << endl;
    cout << "작성자: " << author << endl;
    cout << "작성일: " << date << endl;
    cout << "------------------------" << endl;
    cout << content << endl;
    cout << "========================" << endl;
}
```
- **목적별 분리**: 요약 보기와 상세 보기 함수 분리
- **const 함수**: 객체 상태 변경 없음을 보장

### 3.2 BlogManager 클래스 핵심 기능

#### 안전한 입력 처리
```cpp
int getValidIntegerInput() {
    int input;
    while (!(cin >> input)) {
        cout << "잘못된 입력입니다. 숫자를 입력해주세요: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}
```
- **입력 검증**: 숫자가 아닌 입력에 대한 안전한 처리
- **버퍼 정리**: `cin.ignore()`로 입력 버퍼 정리

#### 게시물 작성 기능
```cpp
void writeNewPost() {
    cout << "\n=== 새 글 쓰기 ===" << endl;
    
    string title, content, author;
    
    cout << "제목을 입력하세요: ";
    getline(cin, title);
    
    if (title.empty()) {
        cout << "제목을 입력해야 합니다!" << endl;
        return;
    }
    
    // 다중 라인 내용 입력 처리
    cout << "내용을 입력하세요 (여러 줄 가능, 빈 줄 입력시 완료): " << endl;
    string line;
    while (getline(cin, line) && !line.empty()) {
        if (!content.empty()) {
            content += "\n";
        }
        content += line;
    }
    
    // ... 유효성 검사 및 객체 생성
    posts.emplace_back(title, content, author);
}
```
- **다중 라인 지원**: 빈 줄 입력까지 내용 받기
- **입력 검증**: 빈 값 입력 방지
- **emplace_back**: 효율적인 객체 생성

#### 게시물 삭제 기능
```cpp
void deletePost() {
    // ... 유효성 검사
    
    cout << "정말로 \"" << posts[index].getTitle() << "\" 글을 삭제하시겠습니까? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (confirm == 'y' || confirm == 'Y') {
        string deletedTitle = posts[index].getTitle();
        posts.erase(posts.begin() + index);
        cout << "\"" << deletedTitle << "\" 글이 삭제되었습니다." << endl;
    }
}
```
- **확인 절차**: 실수로 인한 삭제 방지
- **벡터 원소 제거**: `erase()` 함수 활용

## 4. 실행 화면

### 4.1 메인 메뉴
```
======= 미니 블로그 v1.0 =======
1. 새 글 쓰기
2. 글 목록 보기
3. 글 읽기
4. 글 삭제
5. 종료
===============================
선택하세요 (1-5): 
```

### 4.2 새 글 쓰기 화면
```
=== 새 글 쓰기 ===
제목을 입력하세요: C++ 학습 일기
내용을 입력하세요 (여러 줄 가능, 빈 줄 입력시 완료): 
오늘은 C++로 블로그 시스템을 만들어보았다.
클래스와 벡터를 활용하여 객체지향적으로 설계했다.
생각보다 재미있었다!

작성자를 입력하세요: 홍길동
새 글이 성공적으로 등록되었습니다!
```

### 4.3 글 목록 보기 화면
```
=== 글 목록 ===
총 2개의 글이 있습니다.
--------------------------------------
[0] C++ 학습 일기 | 작성자: 홍길동 | 날짜: Sun May 25 14:30:25 2025
[1] 프로그래밍 팁 | 작성자: 김개발 | 날짜: Sun May 25 14:35:10 2025
--------------------------------------
```

### 4.4 글 읽기 화면
```
읽을 글의 번호를 입력하세요: 0

=== 게시물 상세 보기 ===
제목: C++ 학습 일기
작성자: 홍길동
작성일: Sun May 25 14:30:25 2025
------------------------
오늘은 C++로 블로그 시스템을 만들어보았다.
클래스와 벡터를 활용하여 객체지향적으로 설계했다.
생각보다 재미있었다!
========================
```

### 4.5 글 삭제 화면
```
=== 글 목록 ===
총 2개의 글이 있습니다.
--------------------------------------
[0] C++ 학습 일기 | 작성자: 홍길동 | 날짜: Sun May 25 14:30:25 2025
[1] 프로그래밍 팁 | 작성자: 김개발 | 날짜: Sun May 25 14:35:10 2025
--------------------------------------

삭제할 글의 번호를 입력하세요: 0
정말로 "C++ 학습 일기" 글을 삭제하시겠습니까? (y/n): y
"C++ 학습 일기" 글이 삭제되었습니다.
```

## 5. 예외 상황 처리

### 5.1 잘못된 입력 처리
- **숫자가 아닌 입력**: 재입력 요구
- **범위를 벗어난 인덱스**: 오류 메시지 출력
- **빈 값 입력**: 필수 항목 입력 요구

### 5.2 경계 상황 처리
- **빈 블로그**: "등록된 글이 없습니다" 메시지
- **삭제 확인**: 실수 방지를 위한 확인 절차
- **입력 버퍼**: `cin.ignore()`로 버퍼 정리

## 6. 코드 품질

### 6.1 가독성
- **의미 있는 변수명**: `title`, `content`, `author` 등
- **함수명**: `writeNewPost()`, `showPostList()` 등 동작을 명확히 표현
- **주석**: 각 함수와 중요한 로직에 설명 주석 추가

### 6.2 유지보수성
- **모듈화**: 기능별로 함수 분리
- **캡슐화**: private 멤버로 데이터 보호
- **const 정확성**: 상태 변경하지 않는 함수는 const로 선언

### 6.3 안정성
- **입력 검증**: 모든 사용자 입력에 대한 검증
- **예외 처리**: try-catch로 전체적인 예외 처리
- **메모리 안전성**: 자동 메모리 관리 활용

## 7. 개선 가능한 점

### 7.1 기능 확장
- 글 수정 기능 추가
- 검색 기능 구현
- 파일 저장/불러오기

### 7.2 성능 개선
- 대용량 데이터 처리를 위한 최적화
- 인덱싱 시스템 도입

### 7.3 사용자 인터페이스
- 더 직관적인 메뉴 시스템
- 색상 출력 지원

## 8. 결론

본 프로젝트를 통해 C++의 클래스, 벡터, 문자열 처리 등의 핵심 개념을 실제 애플리케이션에 적용해보았습니다. 객체지향 설계 원칙을 따라 유지보수가 용이하고 확장 가능한 코드를 작성했으며, 다양한 예외 상황을 고려한 안정적인 프로그램을 완성했습니다.

특히 사용자 입력 처리, 데이터 검증, 메모리 관리 등 실제 프로그램 개발에서 중요한 요소들을 경험할 수 있었고, 이는 향후 더 복잡한 시스템 개발의 기초가 될 것입니다.
