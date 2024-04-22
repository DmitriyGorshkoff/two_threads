/*
Создать cmake проект и написать многопоточное приложение на С++.
Одна нитка выделяет 256МБ памяти и по таймеру (задаваемое количество раз в секунду)
заполняет счетчиком 1МБ данных в выделенном циклическом буфере и отправляет в очередь
сообщение с размером и указателем на данные другой нитке которая висит на ожидании сообщений.
При получении сообщения она дописывает эти данные в файл.
Очередь имеет конечную длину 256 и при заполненности выдает ошибку.
По достижению определенного задаваемого обьема данных программа завершается.
В процессе вполнения выдает среднюю скорость записи и количество элементов в очереди.
(использовать std::thread, std::unique_lock, std::condition_variable, std::queue)
Проект закоммитить в github и прислать ссылку.

std::thread, std::unique_lock, std::condition_variable, std::queue
*/

#include <iostream>

#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>


#include "FirstThreadClass.h"
#include "SecondThreadClass.h"
#include "LocalQueue.h"


int main()
{
    FirstThreadClass  FirstObj( 256, 100);
    SecondThreadClass SecondObj;

    LocalQueue Queue(256);
    //std::mutex Queue_mutex;

    std::condition_variable CondVar;

    // Запуск потоков
    std::thread FirstThread(  &FirstThreadClass::work, &FirstObj, &Queue, &CondVar);
    std::thread SecondThread( &SecondThreadClass::work, &SecondObj, &Queue, &CondVar);

    // Ожидание завершения потоков
    FirstThread.join();
    SecondThread.join();

    ////FirstThread.detach();
    ////SecondThread.detach();

    system("pause");

    return 0;
}