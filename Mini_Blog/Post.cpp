#include "Post.h"

/**
 * @brief Post 클래스 생성자
 * @param id 게시글 고유 식별자
 * @param title 게시글 제목
 * @param content 게시글 내용
 * @param author 작성자 이름
 */
Post::Post(int id, const std::string& title, const std::string& content, const std::string& author)
    : id(id), title(title), content(content), author(author) {
    // 현재 시간을 가져와서 날짜 문자열 생성
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    date = buffer;
}

/**
 * @brief 게시글 제목 반환
 * @return 게시글 제목
 */
std::string Post::getTitle() const {
    return title;
}

/**
 * @brief 게시글 내용 반환
 * @return 게시글 내용
 */
std::string Post::getContent() const {
    return content;
}

/**
 * @brief 작성자 이름 반환
 * @return 작성자 이름
 */
std::string Post::getAuthor() const {
    return author;
}

/**
 * @brief 작성 날짜 반환
 * @return 작성 날짜 문자열
 */
std::string Post::getDate() const {
    return date;
}

/**
 * @brief 게시글 ID 반환
 * @return 게시글 고유 식별자
 */
int Post::getId() const {
    return id;
}

/**
 * @brief 게시글 요약 정보 출력
 * 
 * 게시글 목록에서 보여줄 요약 정보(ID, 제목, 작성자, 날짜)를 출력합니다.
 */
void Post::displaySummary() const {
    std::cout << std::left << std::setw(4) << id << " | "
              << std::setw(30) << (title.length() > 28 ? title.substr(0, 25) + "..." : title) << " | "
              << std::setw(15) << (author.length() > 13 ? author.substr(0, 10) + "..." : author) << " | "
              << date << std::endl;
}

/**
 * @brief 게시글 전체 내용 출력
 * 
 * 게시글의 모든 정보(ID, 제목, 작성자, 날짜, 내용)를 출력합니다.
 */
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
