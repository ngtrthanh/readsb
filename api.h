#ifndef API_H
#define API_H

#define API_REQ_PADSTART (192)

struct apiCon {
    int fd;
    int accept;
    struct char_buffer cb;
    int cbOffset;
    uint32_t events;
    struct char_buffer request;
};

struct offset {
    int offset;
    int len;
};

struct apiEntry {
    struct apiEntry *next;
    uint32_t addr;
    int32_t lat;
    int32_t lon;
    int32_t alt;
    struct offset jsonOffset;
    float distance;
    char typeCode[4];
    uint16_t dbFlags;
};

struct apiCircle {
    double lat;
    double lon;
    double radius; // in meters
    bool onlyClosest;
};

struct apiBuffer {
    int len;
    int alloc;
    struct apiEntry *list;
    uint64_t timestamp;
    char *json;
    struct apiEntry **hashList;
    uint32_t focus;
};

struct apiThread {
    pthread_t thread;
    pthread_mutex_t mutex;
    int index;
    int epfd;
    int eventfd;
};

struct range {
    int from; // inclusive
    int to; // exclusive
};

void apiInit();
void apiCleanup();
void apiLockMutex();
void apiUnlockMutex();

int apiUpdate(struct craftArray *ca);

#endif