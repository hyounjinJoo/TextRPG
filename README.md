# 태어난 김에 보스까지

- **프로젝트 소개**
    - 프로젝트 이름
        - 태어난 김에 보스까지
    - 프로젝트 개요
        
        > 이 프로젝트는 텍스트 기반의 RPG 게임입니다.
        > 
        > 
        > 주요 콘텐츠는 이름 설정 후 자동으로 몬스터를 조우하며 전투가 진행됩니다.
        > 
        > 전투 완료 후 상점을 방문하여 아이템을 사고 팔 수 있으며
        > 
        > 해당 아이템은 전투 시 랜덤하게 사용됩니다.
        > 
        > 일정 수치의 레벨을 도달했다면 보스와 전투를 하게 되고 승리한 경우 게임 클리어입니다.
        > 
    - 주요 기능 요약
        - 플레이어
            - 인벤토리 시스템
            - 레벨 업 및 능력치 시스템
        - 몬스터 생성 및 관리
            - 플레이어 레벨에 따른 난이도 조절된 몬스터 생성
            - 몬스터의 체력 및 공격력 관리
        - 자동 전투 및 전투 후 상점 방문
            - 플레이어와 몬스터/보스몬스터와의 자동 전투 진행
            - 전투 종료 시 상점 방문 여부를 묻고 이에 따라 상점에서 상호작용하도록 관리
        - 상점 시스템
            - 플레이어의 인벤토리와 상호작용하여 아이템 구매 및 판매
            - 판매 아이템 표시 기능
    - 사용된 C++ Library
        - std::vector
        - std::string
    - 사용된 디자인 패턴
        - SingleTone : Character 클래스

- **개발 환경**
    - 개발 언어 및 도구
        - IDE: Visual Studio 2022, Rider
        - Compiler: MSVC v143 / C++14
    - 빌드/실행 방법
        - Visual Studio 2022, 혹은 Rider가 설치되어 있어야 합니다.
        - Clone 혹은 Zip 파일로 프로젝트를 다운로드 합니다.
        - 포함된 Solution 파일을 연 후 빌드하여 실행하면 됩니다.

- **프로젝트 구조**
    
    ```less
    
    TEXTRPG
     ┣ main.cpp
     ┣ Item // 아이템 관련 디렉토리
     ┃ ┣ Item.cpp              // 아이템 인터페이스.cpp(파일만 존재)
     ┃ ┣ Item.h                // 아이템 인터페이스 헤더
     ┃ ┣ AttackBoost.cpp       // 공격력 증가 아이템 구현
     ┃ ┣ AttackBoost.h         // 공격력 증가 아이템 헤더
     ┃ ┣ HealthPotion.cpp      // 체력 회복 아이템 구현
     ┃ ┗ HealthPotion.h        // 체력 회복 아이템 회복
     ┃
     ┣ Manager // 매니저 관련 디렉토리
     ┃ ┣ GameManager.cpp       // 게임 매니저 구현
     ┃ ┗ GameManager.h         // 게임 매니저 헤더
     ┃
     ┣ Monster // 몬스터 관련 디렉토리
     ┃ ┣ Monster.h             // 몬스터 인터페이스 헤더
     ┃ ┣ BossMonster.cpp       // 보스 몬스터 구현
     ┃ ┣ BossMonster.h         // 보스 몬스터 헤더
     ┃ ┣ Goblin.cpp            // 고블린 구현
     ┃ ┣ Goblin.h              // 고블린 헤더
     ┃ ┣ Orc.cpp               // 오크 구현
     ┃ ┣ Orc.h                 // 오크 헤더
     ┃ ┣ Troll.cpp             // 트롤 구현
     ┃ ┗ Troll.h               // 트롤 헤더
     ┃
     ┣ Player // 플레이어 관련 디렉토리
     ┃ ┣ Character.cpp         // 플레이어 캐릭터 구현
     ┃ ┗ Character.h           // 플레이어 캐릭터 헤더
     ┃
     ┣ Shop // 샵 관련 디렉토리
     ┃ ┣ Shop.cpp              // 샵 시스템 구현
     ┃ ┗ Shop.h                // 샵 시스템 헤더
     ┃
     ┣ TextRPG.sln             // 솔루션 파일
     ┣ TextRPG.vcxproj         // 프로젝트 파일
     ┗ TextRPG.vcxproj.filters // 프로젝트 필터 파일
    ```
    

- **핵심 로직/클래스 설명**
    - GameManager
    - Item
    - Monster
    - Character
    - Shop

- **과제 추가 구현 사항**
    - 

- **주의사항**
    -
