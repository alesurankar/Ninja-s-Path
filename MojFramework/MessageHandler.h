#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <optional>
#include <utility>

class MessageHandler
{
public:
    MessageHandler();
    void AppToMSG(const std::string& message);
    std::string MSGToClient();
    void ClientToMSG(int x, int y);
    std::optional<std::pair<int, int>> MSGToApp();
    bool GetFirstMessage();
    void FirstMessageSend();
private:
    std::mutex msg_mtx;
    std::mutex pos_mtx;
    std::string msg = "";
    std::queue<std::string> app_messages;
    std::queue<std::pair<int, int>> app_position;
    std::pair<int, int> lastPos;
    std::atomic<bool> firstMessage;
};