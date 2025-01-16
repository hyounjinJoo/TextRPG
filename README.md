<div align=center><img src="https://capsule-render.vercel.app/api?type=slice&text=%20태어난%20김에%20보스까지&desc=-%20TEXT%20RPG%20-&fontSize=36&height=130&fontAlign=80&descAlign=81&fontAlignY=17&descAlignY=37&rotate=8&descrotate=8&animation=fadeIn&color=gradient&customColorList=3" width=2000></div><br><br>

<div align=center>

![rounded-in-photoretrica](https://github.com/user-attachments/assets/2e2f7c60-4e5e-4343-8ef4-942a47947b23)

<br>
<h1> 프로젝트 소개 </h1>

이 프로젝트는 텍스트 기반의 RPG 게임입니다. <br>
주요 콘텐츠는 이름 설정 후 자동으로 몬스터를 조우하며 전투가 진행됩니다. <br>
전투 완료 후 상점을 방문하여 아이템을 사고 팔 수 있으며 해당 아이템은 전투 시 랜덤하게 사용됩니다. <br>
일정 수치의 레벨을 도달했다면 보스와 전투를 하게 되고 승리한 경우 게임 클리어입니다.

<br>
<h1> 기술 스택 </h1>

[![My Skills](https://skillicons.dev/icons?i=cpp,git&theme=light)](https://skillicons.dev) 


<br>
<h1> 주요 기능 </h1>

<h3>[🧙‍♂️] 캐릭터 이름 입력 </h3>

![스크린샷 2025-01-16 150304](https://github.com/user-attachments/assets/6acadd1c-69e2-455a-adc1-f74a3798ea3b) 


<br>
<h3>[🗡️] 몬스터 자동 전투 </h3>

![스크린샷 2025-01-16 150310](https://github.com/user-attachments/assets/d3cadf90-cbd8-44aa-b676-f8936335a51b)



<br>
<h3>[✨] 전투 보상 및 플레이어 상태 표시 </h3>

![스크린샷 2025-01-16 150314](https://github.com/user-attachments/assets/3d75e0dc-6059-4986-a759-ca3ba485439d)




<br>
<h3>[🍻] 상점 방문 </h3>

![스크린샷 2025-01-16 150319](https://github.com/user-attachments/assets/bdc63389-7c5a-45ea-aaa2-1ad6981e5b4d)

<br>
<h3>[🍷] 상점 포션 구매 </h3>

![스크린샷 2025-01-16 150322](https://github.com/user-attachments/assets/e90052e4-2cce-4600-b46d-f82d4c9500d8)

<br>
<h3>[💰] 상점 포션 판매 </h3>

![스크린샷 2025-01-16 151445](https://github.com/user-attachments/assets/5006df74-de28-4a27-a991-a0d154b30425)

<br>
<h3>[🐉] 게임 승리 </h3>

![스크린샷 2025-01-16 152000](https://github.com/user-attachments/assets/1ab7d9b9-2d0a-4899-bb32-54c294b5b280)


<br>
<h3>[📜] 엔딩 크레딧 </h3>

![스크린샷 2025-01-16 152106](https://github.com/user-attachments/assets/e1bd144d-1d62-42c9-8858-035096f77cdf)



<br>
<h1> 프로젝트 구조 </h1>
</div>


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
     ┗ TextRP


<details>
<summary> 프로젝트 소개 </summary>

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
    
</details>

<details>
<summary>주요 기능 요약</summary>

![Project_2](https://github.com/user-attachments/assets/d1e66487-6de0-4623-b4c1-f4196ba1bb32)


</details>

<details>
<summary>C++ 라이브러리 / 디자인패턴</summary>

![Project_3](https://github.com/user-attachments/assets/aa0966d5-eade-4014-a0bd-e2e0d853f44e)

</details>

<details>
<summary> 개발 환경 </summary>

![Project_4](https://github.com/user-attachments/assets/7ac5221e-d58a-4a94-baac-ac2af51e93c8)

</details>

<details>
<summary> 프로젝트 구조 및 클래스 설명 </summary>

![Project_1](https://github.com/user-attachments/assets/63984e54-62fe-4117-b213-eb502604d7aa)

</details>



<details>
<summary> 과제 추가 구현 사항</summary>
    
    - Sound - BGM, 플레이어 공격시 타격음, 엔딩 크레딧에서 타이핑 효과에 소리가 나도록 구현
    - Typing Effect - 문자가 입력되듯이 화면에 출력되는 효과
    - Delay (Thead Lock)
    - Ending Credit  
    
</details>
