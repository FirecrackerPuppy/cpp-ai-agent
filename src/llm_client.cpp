#include "llm_client.h"
#include "../third_party/httplib.h"
#include <iostream>

std::string LLMClient::call(const std::string& prompt) {
    httplib::Client cli("https://api.openai.com");

    httplib::Headers headers = {
        {"Authorization", "Bearer YOUR_API_KEY"},
        {"Content-Type", "application/json"}
    };

    std::string body = R"({
        "model": "gpt-4o-mini",
        "messages": [
            {"role": "user", "content": ")" + prompt + R"("}
        ]
    })";

    auto res = cli.Post("/v1/chat/completions", headers, body, "application/json");

    if (!res) {
        return "{\"action\":\"echo\",\"input\":\"LLM request failed\"}";
    }

    return res->body;
}