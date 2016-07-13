#include <sys/types.h>
#ifndef _WIN32
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif
#include <microhttpd.h>
#include <stdio.h>

#define PORT 8888

int getSum = 0;

static int sumGET(void *cls, enum MHD_ValueKind kind, const char *key, const char *value)
{
    getSum += atoi(value);
    return MHD_YES;
}

static int answerToConnection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method, const char *version,
                                const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND, sumGET, NULL);

    char getSumStr[32];
    sprintf(getSumStr, "%d", getSum);

    getSum = 0;
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(getSumStr), (void *)getSumStr, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answerToConnection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    (void) getc(stdin);

    MHD_stop_daemon(daemon);
    return 0;
}
