#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <list>
#include <memory>

struct HistoryItem {
    uint8_t* data;
    size_t size;
};

int make_history_item(const uint8_t* data, size_t size, HistoryItem **item) {
    if (data == NULL || size == 0)
        return -1;
    *item = (HistoryItem*)malloc(sizeof(HistoryItem));
    if (NULL == *item)
        return -1;
    (*item)->data = (uint8_t*)malloc(size);
    if (NULL == (*item)->data) {
        free(*item);
        return -1;
    }
    memcpy((*item)->data, data, size);
    (*item)->size = size;
    return 0;
}

void free_history_item(HistoryItem* item) {
    free(item->data);
    free(item);
}

std::string handle_command(const uint8_t* data, size_t size) {
    static std::list<std::unique_ptr<HistoryItem, void(*)(HistoryItem*)>> history;
    HistoryItem *item = nullptr;
    if (make_history_item(data, size, &item) < 0)
        throw std::bad_alloc();
    // std::unique_ptr(item, free_history_item);
    // emplace_back + Smart Pointer
    // history.push_back(std::make_unique<HistoryItem, ...>(item, free_history_item));
    if (history.size() > 10)
        history.pop_front();
}

int main()
{
    const uint8_t cmd1[] = {'h','e','l','l','o'};
    const uint8_t cmd2[] = {'w','o','r','d'};
    const uint8_t cmd3[] = {'h','i','s','t','o','r','y'};
    handle_command(cmd1, sizeof(cmd1));
    handle_command(cmd2, sizeof(cmd2));
    handle_command(cmd3, sizeof(cmd3));
    return 0;
}
