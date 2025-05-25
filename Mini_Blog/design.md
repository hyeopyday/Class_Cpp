# 미니 블로그 v1.0 설계 문서

## Post 클래스 설계

### 멤버 변수
- `string title`: 글의 제목
- `string content`: 글의 내용
- `string author`: 작성자 이름
- `string date`: 작성 날짜 (문자열 형태로 저장)
- `int id`: 글의 고유 식별자 (자동 생성)

### 멤버 함수
- `Post(string title, string content, string author)`: 생성자
- `string getTitle() const`: 제목 반환
- `string getContent() const`: 내용 반환
- `string getAuthor() const`: 작성자 반환
- `string getDate() const`: 작성 날짜 반환
- `int getId() const`: 글 ID 반환
- `void displaySummary() const`: 글 목록에서 보여줄 요약 정보 출력
- `void displayFull() const`: 글 전체 내용 출력

## 블로그 관리 클래스 설계 (BlogManager)

### 멤버 변수
- `vector<Post> posts`: 게시글 저장 벡터
- `int nextId`: 다음에 생성될 글의 ID

### 멤버 함수
- `void addPost()`: 새 글 작성 기능
- `void listPosts() const`: 글 목록 보기 기능
- `void viewPost()`: 특정 글 읽기 기능
- `void deletePost()`: 글 삭제 기능
- `void run()`: 메인 메뉴 실행 함수
- `int getPostIndexById(int id) const`: ID로 글 인덱스 찾기
- `bool isEmpty() const`: 게시글이 없는지 확인

## 메인 프로그램 구조
1. BlogManager 객체 생성
2. run() 메서드 호출하여 메인 메뉴 실행
3. 사용자 선택에 따라 해당 기능 실행
4. 종료 옵션 선택 시 프로그램 종료

## 예외 처리 계획
- 빈 벡터에서 글 읽기/삭제 시도 시 처리
- 존재하지 않는 글 ID 입력 시 처리
- 입력값 검증 (빈 제목/내용 등)
- 메뉴 선택 시 잘못된 입력 처리

## 사용자 인터페이스
- 콘솔 기반 메뉴 시스템
- 명확한 안내 메시지 제공
- 각 작업 후 적절한 피드백 제공
