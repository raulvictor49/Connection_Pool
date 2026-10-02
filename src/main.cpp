#include "../include/ConnectionPool.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <string>

void executar_requisicao(int id_thread, ConnectionPool& pool) {
    std::string id_str = (id_thread < 10 ? "0" : "") + std::to_string(id_thread);
    
    std::cout << "[Thread " << id_str << "] solicitando conexao...\n";
    
    int id_conexao = pool.acquire();
    
    std::cout << "[Thread " << id_str << "] conectada (Conexao " << id_conexao 
              << "). Conexoes em uso: " << (5 - pool.availableCount()) << "/5\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(400 + (id_thread * 20)));

    std::cout << "[Thread " << id_str << "] liberou conexao " << id_conexao << ".\n";
    
    pool.release(id_conexao);
}

int main() {
    std::cout << "=== INICIANDO SERVIDOR COM POOL DE CONEXOES ===\n\n";

    ConnectionPool pool(5);
    
    std::vector<std::thread> threads;
    int TOTAL_THREADS = 20;

    for (int i = 1; i <= TOTAL_THREADS; ++i) {
        threads.emplace_back(executar_requisicao, i, std::ref(pool));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\n=== TODAS AS REQUISICOES FORAM PROCESSADAS ===\n";
    return 0;
}