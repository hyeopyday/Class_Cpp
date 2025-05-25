#include "BlogManager.h"
#include <iostream>
#include <limits>
#include <algorithm>

/**
 * @brief BlogManager 클래스 생성자
 */
BlogManager::BlogManager() : nextId(1) {
    // 초기화: 다음 ID는 1부터 시작
}

/**
 * @brief ID로 게시글 인덱스 찾기
 * @param id 찾을 게시글의 ID
 * @return 벡터 내 인덱스 (없으면 -1)
 */
int BlogManager::getPostIndexById(int id) const {
    for (size_t i = 0; i < posts.size(); ++i) {
        if (posts[i].getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1; // 찾지 못한 경우
}

/**
 * @brief 새 게시글 작성 기능
 * 
 * 사용자로부터 제목, 내용, 작성자를 입력받아
 * 새 게시글을 생성하고 벡터에 추가합니다.
 */
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

/**
 * @brief 게시글 목록 보기 기능
 * 
 * 저장된 모든 게시글의 요약 정보를 출력합니다.
 * @return 게시글이 있으면 true, 없으면 false
 */
bool BlogManager::listPosts() const {
    if (posts.empty()) {
        std::cout << "\n등록된 게시글이 없습니다.\n";
        return false;
    }
    
    std::cout << "\n=== 게시글 목록 ===\n";
    std::cout << std::left << std::setw(4) << "ID" << " | "
              << std::setw(30) << "제목" << " | "
              << std::setw(15) << "작성자" << " | "
              << "작성일" << std::endl;
    std::cout << "----------------------------------------------------------------------\n";
    
    for (const auto& post : posts) {
        post.displaySummary();
    }
    
    return true;
}

/**
 * @brief 특정 게시글 읽기 기능
 * 
 * 사용자로부터 게시글 ID를 입력받아
 * 해당 게시글의 전체 내용을 출력합니다.
 */
void BlogManager::viewPost() {
    if (!listPosts()) {
        return; // 게시글이 없으면 함수 종료
    }
    
    int id;
    std::cout << "\n읽을 게시글 ID를 입력하세요: ";
    
    // 유효한 정수 입력 확인
    while (!(std::cin >> id)) {
        std::cin.clear(); // 오류 상태 초기화
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
        std::cout << "유효한 ID를 입력하세요: ";
    }
    std::cin.ignore(); // 버퍼에 남은 개행 문자 제거
    
    int index = getPostIndexById(id);
    if (index == -1) {
        std::cout << "\nID " << id << "번 게시글을 찾을 수 없습니다.\n";
        return;
    }
    
    std::cout << "\n";
    posts[index].displayFull();
}

/**
 * @brief 게시글 삭제 기능
 * 
 * 사용자로부터 게시글 ID를 입력받아
 * 해당 게시글을 벡터에서 삭제합니다.
 */
void BlogManager::deletePost() {
    if (!listPosts()) {
        return; // 게시글이 없으면 함수 종료
    }
    
    int id;
    std::cout << "\n삭제할 게시글 ID를 입력하세요: ";
    
    // 유효한 정수 입력 확인
    while (!(std::cin >> id)) {
        std::cin.clear(); // 오류 상태 초기화
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
        std::cout << "유효한 ID를 입력하세요: ";
    }
    std::cin.ignore(); // 버퍼에 남은 개행 문자 제거
    
    int index = getPostIndexById(id);
    if (index == -1) {
        std::cout << "\nID " << id << "번 게시글을 찾을 수 없습니다.\n";
        return;
    }
    
    // 삭제 확인
    char confirm;
    std::cout << "정말로 '" << posts[index].getTitle() << "' 게시글을 삭제하시겠습니까? (y/n): ";
    std::cin >> confirm;
    std::cin.ignore(); // 버퍼에 남은 개행 문자 제거
    
    if (confirm == 'y' || confirm == 'Y') {
        posts.erase(posts.begin() + index);
        std::cout << "\n게시글이 성공적으로 삭제되었습니다.\n";
    } else {
        std::cout << "\n삭제가 취소되었습니다.\n";
    }
}

/**
 * @brief 게시글이 없는지 확인
 * @return 게시글이 없으면 true, 있으면 false
 */
bool BlogManager::isEmpty() const {
    return posts.empty();
}

/**
 * @brief 메인 메뉴 실행 함수
 * 
 * 사용자에게 메뉴를 표시하고 선택에 따라
 * 해당 기능을 실행하는 메인 루프입니다.
 */
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
