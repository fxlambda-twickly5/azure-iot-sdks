# iothubtransportamqp_core_common Requirements

## Overview

This is a library that contains common functions used by the implementations of the iothubtransportamqp_core modules.


## Dependencies

This module will depend on the following modules:

azure-c-shared-utilities
azure-c-uamqp


## Exposed API

```c
typedef enum CONNECTION_ERROR_CODE
{
    CONNECTION_ERROR,
    CONNECTION_CBS_ERROR
};

typedef (void)(*ON_CONNECTION_ERROR_CALLBACK)(CONNECTION_ERROR_CODE error_code, const void* context);

typedef struct AMQP_CONNECTION_CONFIG_TAG
{
    const char* iothub_host_fqdn;
    XIO_HANDLE xio_handle;
    bool create_sasl_io;
    bool create_cbs_connection;
    bool is_trace_on;

    ON_CONNECTION_ERROR_CALLBACK on_error_callback;
    const void* on_error_context;
} AMQP_CONNECTION_CONFIG;

typedef struct AMQP_CONNECTION_STATE* AMQP_CONNECTION_HANDLE;

int get_seconds_since_epoch(double* seconds);

AMQP_CONNECTION_HANDLE amqp_connection_create(AMQP_CONNECTION_CONFIG* config);

void amqp_connection_destroy(AMQP_CONNECTION_HANDLE conn_handle);

void amqp_connection_do_work(AMQP_CONNECTION_HANDLE conn_handle);

int amqp_connection_get_session(AMQP_CONNECTION_HANDLE conn_handle, SESSION_HANDLE* session_handle);
```



## get_seconds_since_epoch

```c
int get_seconds_since_epoch(double* seconds);
```

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If parameter `seconds`, get_seconds_since_epoch() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**The current time shall be obtained with get_time((time_t)NULL)**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If get_time() fails, get_seconds_since_epoch() shall fail and return __NULL__**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**The number of seconds since epoch shall be obtained with get_difftime()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If no failures occurr, get_seconds_since_epoch() shall return the result of get_difftime()**]**


## amqp_connection_create

```c
AMQP_CONNECTION_HANDLE amqp_connection_create(AMQP_CONNECTION_CONFIG* config);
```
// TODO: why are iothub_host_fqdn and xio_handle need to saved? they are used only once, on _create().

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `config` is NULL, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `config->iothub_host_fqdn` is NULL, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `config->xio_handle` is NULL, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `config->create_cbs_connection` is true, `config->create_sasl_io` shall be assumed as true**]**

*SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_create() shall allocate memory for an instance of the connection state**]**
*SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If malloc() fails, amqp_connection_create() shall fail and return NULL**]**

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`config->iothub_host_fqdn` shall be saved on `state->iothub_host_fqdn`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`config->xio_handle` shall be saved on `state->base_io`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `config->create_sasl_io` is false, amqp_connection_create() shall use the `state->base_io` as the `connection_underlying_io`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`config->is_trace_on` shall be saved on `state->is_trace_on`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`config->on_error_callback` shall be saved on `state->on_error_callback`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`config->on_error_context` shall be saved on `state->on_error_context`**]**

### Creating SASL instances 
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**Only if `config->create_sasl_io` is true, amqp_connection_create() shall create SASL I/O**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`state->sasl_mechanism` shall be created using saslmechanism_create()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If saslmechanism_create() fails, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**A SASLCLIENTIO_CONFIG shall be set with `state->base_io` and `state->sasl_mechanism`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`state->sasl_io` shall be created using xio_create() passing saslclientio_get_interface_description() and the SASLCLIENTIO_CONFIG instance**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If xio_create() fails, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**The sasl_io "logtrace" option shall be set using xio_setoption(), passing `state->is_trace_on`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_create() shall use the `state->sasl_io` as the `connection_underlying_io`**]**

### Creating the connection and session
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`state->connection_handle` shall be created using connection_create2(), passing the `connection_underlying_io`, `state->iothub_host_fqdn` and any string as container id**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**connection_create2() shall also receive a callback for tracking connection I/O errors**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If connection_create2() fails, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If the connection calls back with an I/O error, `state->on_error_callback` shall be invoked if set passing code CONNECTION_ERROR and `state->on_error_context`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**The connection tracing shall be set using connection_set_trace(), passing `state->is_trace_on`**]**

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`state->session_handle` shall be created using session_create(), passing `state->connection_handle`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If session_create() fails, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**The `state->session_handle` incoming window size shall be set as UINT_MAX using session_set_incoming_window()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**The `state->session_handle` outgoing window size shall be set as 100 using session_set_outgoing_window()**]**

### Creating the CBS instance
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**Only if `config->create_cbs_connection` is true, amqp_connection_create() shall create and open the CBS_HANDLE**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`state->cbs_handle` shall be created using cbs_create(), passing `state->session_handle` and a callback to track its state**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If cbs_create() fails, amqp_connection_create() shall fail and return NULL**]**

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`state->cbs_handle` shall be opened using cbs_open()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If cbs_open() fails, amqp_connection_create() shall fail and return NULL**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If the cbs_open() calls back with an error, `state->on_error_callback` shall be invoked if set passing code CONNECTION_CBS_ERROR and `state->on_error_context`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If no failures occurr, amqp_connection_create() shall return the handle to the connection state**]**


## amqp_connection_destroy

```c
void amqp_connection_destroy(AMQP_CONNECTION_HANDLE conn_handle);
```

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `conn_handle` is NULL, amqp_connection_destroy() shall fail and return**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_destroy() shall destroy `state->cbs_handle` if set using cbs_destroy()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_destroy() shall destroy `state->session_handle` if set using session_destroy()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_destroy() shall destroy `state->sasl_io` if set using xio_destroy()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_destroy() shall destroy `state->sasl_mechanism` if set using saslmechanism_destroy()**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_destroy() shall free the memory allocated for the connectio state**]**


## amqp_connection_do_work

```c
void amqp_connection_do_work(AMQP_CONNECTION_HANDLE conn_handle);
```

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `conn_handle` is NULL, amqp_connection_do_work() shall fail and return**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**connection_dowork() shall be invoked passing `state->connection_handle`**]**


## amqp_connection_get_session

```c
int amqp_connection_get_session(AMQP_CONNECTION_HANDLE conn_handle, SESSION_HANDLE* session_handle);
```

**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `conn_handle` is NULL, amqp_connection_get_session() shall fail and return __LINE__**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**If `session_handle` is NULL, amqp_connection_get_session() shall fail and return __LINE__**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**`session_handle` shall be set to point to `state->session_handle`**]**
**SRS_IOTHUBTRANSPORTAMQP_CORE_COMMON_09_001: [**amqp_connection_get_session() shall return success code 0**]**

