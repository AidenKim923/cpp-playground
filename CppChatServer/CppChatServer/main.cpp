#include <iostream>
#include <winsock2.h>

using namespace std;

int main() {
	// IOCP ������ �����մϴ�.
	SOCKET socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ������ ���ε��մϴ�.
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(socket, (sockaddr*)&addr, sizeof(addr));

	// ������ �������մϴ�.
	listen(socket, 5);

	// Ŭ���̾�Ʈ�� ���� ��û�� �����մϴ�.
	SOCKET client = accept(socket, NULL, NULL);

	// Ŭ���̾�Ʈ�� ä���� �����մϴ�.
	char buffer[1024];
	while (true) {
		// Ŭ���̾�Ʈ�κ��� �����͸� �����մϴ�.
		int bytesReceived = recv(client, buffer, sizeof(buffer), 0);

		// �����Ͱ� ���ŵ��� ������ ä���� �����մϴ�.
		if (bytesReceived == 0) {
			break;
		}

		// ���ŵ� �����͸� UTF-8�� ���ڵ��մϴ�.
		string message = wstring_convert < codecvt_utf8<char>>().to_bytes(buffer, buffer + bytesReceived);

		// �޽����� ����մϴ�.
		cout << message << endl;

		// �޽����� Ŭ���̾�Ʈ�� �����մϴ�.
		int bytesSent = send(client, message.c_str(), message.length(), 0);

		// �޽����� ���۵��� ������ ä���� �����մϴ�.
		if (bytesSent == 0) {
			break;
		}
	}

	// Ŭ���̾�Ʈ���� ������ �����մϴ�.
	closesocket(client);

	return 0;
}