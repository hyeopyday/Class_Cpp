#ifndef POST_H
#define POST_H

#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>

/**
 * @class Post
 * @brief 블로그 게시글을 나타내는 클래스
 * 
 * 블로그 게시글의 제목, 내용, 작성자, 작성일자 등의 정보를 저장하고
 * 관련 기능을 제공하는 클래스입니다.
 */
class Post {
private:
    int id;             ///< 게시글 고유 식별자
    std::string title;  ///< 게시글 제목
    std::string content; ///< 게시글 내용
    std::string author;  ///< 작성자 이름
    std::string date;    ///< 작성 날짜 (문자열)

public:
    /**
     * @brief Post 클래스 생성자
     * @param id 게시글 고유 식별자
     * @param title 게시글 제목
     * @param content 게시글 내용
     * @param author 작성자 이름
     */
    Post(int id, const std::string& title, const std::string& content, const std::string& author);
    
    /**
     * @brief 게시글 제목 반환
     * @return 게시글 제목
     */
    std::string getTitle() const;
    
    /**
     * @brief 게시글 내용 반환
     * @return 게시글 내용
     */
    std::string getContent() const;
    
    /**
     * @brief 작성자 이름 반환
     * @return 작성자 이름
     */
    std::string getAuthor() const;
    
    /**
     * @brief 작성 날짜 반환
     * @return 작성 날짜 문자열
     */
    std::string getDate() const;
    
    /**
     * @brief 게시글 ID 반환
     * @return 게시글 고유 식별자
     */
    int getId() const;
    
    /**
     * @brief 게시글 요약 정보 출력
     * 
     * 게시글 목록에서 보여줄 요약 정보(ID, 제목, 작성자, 날짜)를 출력합니다.
     */
    void displaySummary() const;
    
    /**
     * @brief 게시글 전체 내용 출력
     * 
     * 게시글의 모든 정보(ID, 제목, 작성자, 날짜, 내용)를 출력합니다.
     */
    void displayFull() const;
};

#endif // POST_H
