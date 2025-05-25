#include "BlogManager.h"
#include <iostream>

/**
 * @file main.cpp
 * @brief 미니 블로그 v1.0 메인 프로그램
 * 
 * 블로그 관리 시스템을 초기화하고 실행하는 메인 함수입니다.
 */

/**
 * @brief 프로그램 시작점
 * @return 프로그램 종료 코드
 */
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
