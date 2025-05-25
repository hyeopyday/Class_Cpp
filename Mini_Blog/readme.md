# 미니 블로그 v1.0 개발 보고서

## 1. 프로그램 개요

본 프로그램은 사용자가 짧은 글을 작성하여 저장하고 목록을 보거나 특정 글을 자세히 볼 수 있는 간단한 블로그 시스템입니다. C++의 벡터를 활용하여 게시글을 관리하며, 객체지향 프로그래밍 원칙에 따라 설계되었습니다.

## 2. 프로그램 설계

### 2.1 클래스 구조

프로그램은 크게 두 개의 클래스로 구성되어 있습니다:

1. **Post 클래스**: 개별 게시글의 정보와 기능을 담당
2. **BlogManager 클래스**: 게시글 컬렉션 관리 및 사용자 인터페이스 담당

### 2.2 Post 클래스 설계

#### 멤버 변수
- `int id`: 게시글 고유 식별자
- `string title`: 게시글 제목
- `string content`: 게시글 내용
- `string author`: 작성자 이름
- `string date`: 작성 날짜 (자동 생성)

#### 멤버 함수
- 생성자: 게시글 정보 초기화 및 날짜 자동 생성
- Getter 함수들: 각 멤버 변수에 대한 접근자
- `displaySummary()`: 목록에서 보여줄 요약 정보 출력
- `displayFull()`: 게시글 전체 내용 출력

### 2.3 BlogManager 클래스 설계

#### 멤버 변수
- `vector<Post> posts`: 게시글 저장 벡터
- `int nextId`: 다음에 생성될 글의 ID

#### 멤버 함수
- `addPost()`: 새 글 작성 기능
- `listPosts()`: 글 목록 보기 기능
- `viewPost()`: 특정 글 읽기 기능
- `deletePost()`: 글 삭제 기능
- `getPostIndexById()`: ID로 글 인덱스 찾기
- `isEmpty()`: 게시글이 없는지 확인
- `run()`: 메인 메뉴 실행 함수

### 2.4 프로그램 흐름

1. 프로그램 시작 시 BlogManager 객체 생성
2. 메인 메뉴 표시 (새 글 작성, 목록 보기, 글 읽기, 글 삭제, 종료)
3. 사용자 선택에 따라 해당 기능 실행
4. 종료 옵션 선택 시 프로그램 종료

## 3. 주요 코드 설명

### 3.1 Post 클래스

```cpp
// Post.h
class Post {
private:
    int id;             // 게시글 고유 식별자
    std::string title;  // 게시글 제목
    std::string content; // 게시글 내용
    std::string author;  // 작성자 이름
    std::string date;    // 작성 날짜 (문자열)

public:
    // 생성자
    Post(int id, const std::string& title, const std::string& content, const std::string& author);
    
    // Getter 함수들
    std::string getTitle() const;
    std::string getContent() const;
    std::string getAuthor() const;
    std::string getDate() const;
    int getId() const;
    
    // 출력 함수들
    void displaySummary() const;
    void displayFull() const;
};
```

생성자에서는 현재 시간을 가져와 날짜 문자열을 생성합니다:

```cpp
// Post.cpp
Post::Post(int id, const std::string& title, const std::string& content, const std::string& author)
    : id(id), title(title), content(content), author(author) {
    // 현재 시간을 가져와서 날짜 문자열 생성
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    date = buffer;
}
```

게시글 출력 함수들은 정보를 보기 좋게 포맷팅합니다:

```cpp
// Post.cpp
void Post::displaySummary() const {
    std::cout << std::left << std::setw(4) << id << " | "
              << std::setw(30) << (title.length() > 28 ? title.substr(0, 25) + "..." : title) << " | "
              << std::setw(15) << (author.length() > 13 ? author.substr(0, 10) + "..." : author) << " | "
              << date << std::endl;
}

void Post::displayFull() const {
    std::cout << "=======================================================" << std::endl;
    std::cout << "글 번호: " << id << std::endl;
    std::cout << "제목: " << title << std::endl;
    std::cout << "작성자: " << author << std::endl;
    std::cout << "작성일: " << date << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << content << std::endl;
    std::cout << "=======================================================" << std::endl;
}
```

### 3.2 BlogManager 클래스

BlogManager 클래스는 게시글 관리와 사용자 인터페이스를 담당합니다:

```cpp
// BlogManager.h
class BlogManager {
private:
    std::vector<Post> posts; // 게시글 저장 벡터
    int nextId;              // 다음에 생성될 글의 ID

    // ID로 게시글 인덱스 찾기
    int getPostIndexById(int id) const;

public:
    // 생성자
    BlogManager();

    // 주요 기능 함수들
    void addPost();
    bool listPosts() const;
    void viewPost();
    void deletePost();
    bool isEmpty() const;
    void run();
};
```

새 글 작성 기능은 사용자 입력을 받아 Post 객체를 생성합니다:

```cpp
// BlogManager.cpp
void BlogManager::addPost() {
    std::string title, content, author;
    
    std::cout << "\n=== 새 글 작성 ===\n";
    
    // 제목 입력 (빈 제목 방지)
    do {
        std::cout << "제목: ";
        std::getline(std::cin, title);
        if (title.empty()) {
            std::cout << "제목을 입력해주세요.\n";
        }
    } while (title.empty());
    
    // 작성자 입력 (빈 작성자 방지)
    do {
        std::cout << "작성자: ";
        std::getline(std::cin, author);
        if (author.empty()) {
            std::cout << "작성자를 입력해주세요.\n";
        }
    } while (author.empty());
    
    // 내용 입력 (빈 내용 허용)
    std::cout << "내용 (입력 완료 후 빈 줄에서 Enter): \n";
    std::string line;
    content = "";
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        content += line + "\n";
    }
    
    // 새 게시글 생성 및 추가
    Post newPost(nextId++, title, content, author);
    posts.push_back(newPost);
    
    std::cout << "\n게시글이 성공적으로 등록되었습니다.\n";
}
```

메인 메뉴 실행 함수는 사용자 선택에 따라 기능을 실행합니다:

```cpp
// BlogManager.cpp
void BlogManager::run() {
    int choice;
    bool running = true;
    
    while (running) {
        std::cout << "\n=== 미니 블로그 v1.0 ===\n";
        std::cout << "1. 새 글 작성\n";
        std::cout << "2. 글 목록 보기\n";
        std::cout << "3. 글 읽기\n";
        std::cout << "4. 글 삭제\n";
        std::cout << "0. 종료\n";
        std::cout << "선택: ";
        
        // 유효한 메뉴 선택 확인
        if (!(std::cin >> choice)) {
            std::cin.clear(); // 오류 상태 초기화
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
            std::cout << "\n유효한 메뉴 번호를 입력하세요.\n";
            continue;
        }
        std::cin.ignore(); // 버퍼에 남은 개행 문자 제거
        
        switch (choice) {
            case 1:
                addPost();
                break;
            case 2:
                listPosts();
                break;
            case 3:
                viewPost();
                break;
            case 4:
                deletePost();
                break;
            case 0:
                std::cout << "\n프로그램을 종료합니다. 감사합니다.\n";
                running = false;
                break;
            default:
                std::cout << "\n유효한 메뉴 번호를 입력하세요.\n";
                break;
        }
    }
}
```

### 3.3 메인 함수

메인 함수는 간단하게 BlogManager 객체를 생성하고 실행합니다:

```cpp
// main.cpp
int main() {
    // 콘솔 출력 인코딩 설정 (한글 지원)
    std::cout.sync_with_stdio(false);
    
    // 블로그 관리자 객체 생성
    BlogManager blogManager;
    
    // 시작 메시지 출력
    std::cout << "미니 블로그 v1.0에 오신 것을 환영합니다!" << std::endl;
    std::cout << "간단한 블로그 시스템을 통해 글을 작성하고 관리할 수 있습니다." << std::endl;
    
    // 메인 메뉴 실행
    blogManager.run();
    
    return 0;
}
```

## 4. 예외 처리

프로그램은 다양한 예외 상황을 처리합니다:

1. **빈 입력 처리**: 제목과 작성자는 빈 값을 허용하지 않습니다.
2. **잘못된 메뉴 선택**: 숫자가 아닌 입력이나 범위를 벗어난 선택을 처리합니다.
3. **존재하지 않는 글 접근**: 없는 ID의 글을 읽거나 삭제하려 할 때 오류 메시지를 표시합니다.
4. **빈 게시글 목록**: 게시글이 없을 때 적절한 메시지를 표시합니다.
5. **삭제 확인**: 글 삭제 전 사용자에게 확인을 요청합니다.

## 5. 각 기능별 실행 화면

### 5.1 프로그램 시작 화면

프로그램을 실행하면 다음과 같은 메인 메뉴가 표시됩니다:

```
미니 블로그 v1.0에 오신 것을 환영합니다!
간단한 블로그 시스템을 통해 글을 작성하고 관리할 수 있습니다.

=== 미니 블로그 v1.0 ===
1. 새 글 작성
2. 글 목록 보기
3. 글 읽기
4. 글 삭제
0. 종료
선택: 
```

### 5.2 새 글 작성 기능

메뉴에서 1을 선택하면 새 글을 작성할 수 있습니다:

```
=== 새 글 작성 ===
제목: 첫 번째 게시글
작성자: 홍길동
내용 (입력 완료 후 빈 줄에서 Enter): 
안녕하세요!
이것은 미니 블로그의 첫 번째 게시글입니다.
잘 작동하는지 테스트 중입니다.

게시글이 성공적으로 등록되었습니다.
```

### 5.3 글 목록 보기 기능

메뉴에서 2를 선택하면 등록된 게시글 목록을 볼 수 있습니다:

```
=== 게시글 목록 ===
ID  | 제목                           | 작성자           | 작성일
----------------------------------------------------------------------
1   | 첫 번째 게시글                  | 홍길동           | 2025-05-25 12:30:45
2   | 두 번째 게시글                  | 김철수           | 2025-05-25 12:35:22
```

게시글이 없는 경우:

```
등록된 게시글이 없습니다.
```

### 5.4 글 읽기 기능

메뉴에서 3을 선택하면 특정 게시글을 읽을 수 있습니다:

```
=== 게시글 목록 ===
ID  | 제목                           | 작성자           | 작성일
----------------------------------------------------------------------
1   | 첫 번째 게시글                  | 홍길동           | 2025-05-25 12:30:45
2   | 두 번째 게시글                  | 김철수           | 2025-05-25 12:35:22

읽을 게시글 ID를 입력하세요: 1

=======================================================
글 번호: 1
제목: 첫 번째 게시글
작성자: 홍길동
작성일: 2025-05-25 12:30:45
=======================================================
안녕하세요!
이것은 미니 블로그의 첫 번째 게시글입니다.
잘 작동하는지 테스트 중입니다.
=======================================================
```

존재하지 않는 ID를 입력한 경우:

```
ID 5번 게시글을 찾을 수 없습니다.
```

### 5.5 글 삭제 기능

메뉴에서 4를 선택하면 게시글을 삭제할 수 있습니다:

```
=== 게시글 목록 ===
ID  | 제목                           | 작성자           | 작성일
----------------------------------------------------------------------
1   | 첫 번째 게시글                  | 홍길동           | 2025-05-25 12:30:45
2   | 두 번째 게시글                  | 김철수           | 2025-05-25 12:35:22

삭제할 게시글 ID를 입력하세요: 2
정말로 '두 번째 게시글' 게시글을 삭제하시겠습니까? (y/n): y

게시글이 성공적으로 삭제되었습니다.
```

삭제를 취소한 경우:

```
삭제가 취소되었습니다.
```

## 6. 결론

미니 블로그 v1.0은 C++의 객체지향 프로그래밍 원칙을 활용하여 간단하지만 기능적인 블로그 시스템을 구현했습니다. 프로그램은 사용자가 글을 작성하고, 목록을 보고, 특정 글을 읽고, 삭제할 수 있는 기본적인 CRUD(Create, Read, Update, Delete) 기능을 제공합니다.

코드는 가독성과 유지보수성을 고려하여 작성되었으며, 다양한 예외 상황을 처리하여 안정적으로 동작합니다. 또한 주석을 통해 코드의 이해를 돕고, 사용자 인터페이스를 통해 직관적인 사용이 가능하도록 설계되었습니다.

향후 개선 방향으로는 글 수정 기능 추가, 파일 저장 기능 구현, 검색 기능 추가 등이 있을 수 있습니다.
