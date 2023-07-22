#include <iostream>
#include <winsock2.h>

using namespace std;

int main() {
	// IOCP 소켓을 생성합니다.
	SOCKET socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 소켓을 바인드합니다.
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(socket, (sockaddr*)&addr, sizeof(addr));

	// 소켓을 리스닝합니다.
	listen(socket, 5);

	// 클라이언트의 연결 요청을 수신합니다.
	SOCKET client = accept(socket, NULL, NULL);

	// 클라이언트와 채팅을 시작합니다.
	char buffer[1024];
	while (true) {
		// 클라이언트로부터 데이터를 수신합니다.
		int bytesReceived = recv(client, buffer, sizeof(buffer), 0);

		// 데이터가 수신되지 않으면 채팅을 종료합니다.
		if (bytesReceived == 0) {
			break;
		}

		// 수신된 데이터를 UTF-8로 디코딩합니다.
		string message = wstring_convert < codecvt_utf8<char>>().to_bytes(buffer, buffer + bytesReceived);

		// 메시지를 출력합니다.
		cout << message << endl;

		// 메시지를 클라이언트로 전송합니다.
		int bytesSent = send(client, message.c_str(), message.length(), 0);

		// 메시지가 전송되지 않으면 채팅을 종료합니다.
		if (bytesSent == 0) {
			break;
		}
	}

	// 클라이언트와의 연결을 종료합니다.
	closesocket(client);

	return 0;
}