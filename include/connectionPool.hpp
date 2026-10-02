#ifndef CONNECTION_POOL_HPP
#define CONNECTION_POOL_HPP

#include <mutex>
#include <condition_variable>
#include <vector>

class ConnectionPool {
private:
    std::mutex mtx;
    std::condition_variable cv;

    int total_conexoes;
    int conexoes_ocupadas;
    std::vector<bool> status_conexoes; 

public:
    ConnectionPool(int qtd_conexoes = 5);
    ~ConnectionPool() = default;

    int acquire();
    void release(int id_conexao);
    int availableCount();
};

#endif