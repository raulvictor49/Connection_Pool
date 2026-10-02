#include "../include/ConnectionPool.hpp"

ConnectionPool::ConnectionPool(int qtd_conexoes) 
    : total_conexoes(qtd_conexoes), conexoes_ocupadas(0) {
    status_conexoes.resize(total_conexoes, true);
}

int ConnectionPool::acquire() {
    std::unique_lock<std::mutex> lock(mtx);

    while (conexoes_ocupadas >= total_conexoes) {
        cv.wait(lock); 
    }

    int id_alocado = -1;
    for (int i = 0; i < total_conexoes; ++i) {
        if (status_conexoes[i]) {
            status_conexoes[i] = false;
            id_alocado = i;
            break;
        }
    }
    conexoes_ocupadas++;
    
    return id_alocado; 
}

void ConnectionPool::release(int id_conexao) {
    std::unique_lock<std::mutex> lock(mtx);

    status_conexoes[id_conexao] = true;
    conexoes_ocupadas--;

    cv.notify_one(); 
}

int ConnectionPool::availableCount() {
    std::unique_lock<std::mutex> lock(mtx);
    return total_conexoes - conexoes_ocupadas;
}