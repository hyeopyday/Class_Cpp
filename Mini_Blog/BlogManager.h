#ifndef BLOG_MANAGER_H
#define BLOG_MANAGER_H

#include <vector>
#include "Post.h"

/**
 * @class BlogManager
 * @brief 블로그 게시글을 관리하는 클래스
 * 
 * 게시글 추가, 조회, 삭제 등의 기능을 제공하고
 * 사용자 인터페이스를 관리하는 클래스입니다.
 */
class BlogManager {
private:
    std::vector<Post> posts; ///< 게시글 저장 벡터
    int nextId;              ///< 다음에 생성될 글의 ID

    /**
     * @brief ID로 게시글 인덱스 찾기
     * @param id 찾을 게시글의 ID
     * @return 벡터 내 인덱스 (없으면 -1)
     */
    int getPostIndexById(int id) const;

public:
    /**
     * @brief BlogManager 클래스 생성자
     */
    BlogManager();

    /**
     * @brief 새 게시글 작성 기능
     * 
     * 사용자로부터 제목, 내용, 작성자를 입력받아
     * 새 게시글을 생성하고 벡터에 추가합니다.
     */
    void addPost();

    /**
     * @brief 게시글 목록 보기 기능
     * 
     * 저장된 모든 게시글의 요약 정보를 출력합니다.
     * @return 게시글이 있으면 true, 없으면 false
     */
    bool listPosts() const;

    /**
     * @brief 특정 게시글 읽기 기능
     * 
     * 사용자로부터 게시글 ID를 입력받아
     * 해당 게시글의 전체 내용을 출력합니다.
     */
    void viewPost();

    /**
     * @brief 게시글 삭제 기능
     * 
     * 사용자로부터 게시글 ID를 입력받아
     * 해당 게시글을 벡터에서 삭제합니다.
     */
    void deletePost();

    /**
     * @brief 게시글이 없는지 확인
     * @return 게시글이 없으면 true, 있으면 false
     */
    bool isEmpty() const;

    /**
     * @brief 메인 메뉴 실행 함수
     * 
     * 사용자에게 메뉴를 표시하고 선택에 따라
     * 해당 기능을 실행하는 메인 루프입니다.
     */
    void run();
};

#endif // BLOG_MANAGER_H
