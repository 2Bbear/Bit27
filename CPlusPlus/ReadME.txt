0305

-Skelletone Code - 실제 프로그램 코드 부분
winMain
1.form 생성
	실제 윈도우 창을 디자인하는 위치
2.Message Loop 
	프로그램이 종료되기 전까지 무한 루프하는 부분
	2.2 자기 자신의 어플리케이션의 msg를 가져오기
	2.3 가져온 msg를 적절한 function으로 처리하기 -> 종료 -> 다시 루프 반복 == 메세지를 처리하는 일련의 과정 == 메세지 프로시저	
	
- 사용자 화면 - OS 처리 부분
1. 사용자가 event를 발생시킴
2. 발생된 event(시간, 키보드 마우스 입력값 등)는 msg라는 메세지로 변환
3. 변환된 msg를 SYstem Q에 저장함
4. System Q - 분배기
	분배기는 msq를 추출해서 내용을 분석을 함
5. 분배기 , Application-Application Q
	분석된 내용은 적절한 Application에 명령이 분배됨
	적절한 Application은 핸들값으로 지정된다.
	따라서 분배기는 Application의 핸들값을 가지고 있어야 한다. 그래야 분배를 할 수 있으니까
	*Application Q는 모든 Application이 가지고 있는 Q / 프로그램이 10개가 실행되고 있으면 Application Q도 10개가 있다.
