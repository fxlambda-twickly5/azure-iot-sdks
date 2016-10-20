// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUBTRANSPORTAMQP_MESSENGER_H
#define IOTHUBTRANSPORTAMQP_MESSENGER_H

#include "azure_c_shared_utility\doublylinkedlist.h"
#include "azure_uamqp_c\session.h"
#include "iothub_message.h"

#ifdef __cplusplus
extern "C"
{
#endif
	typedef enum MESSENGER_ERROR_CODE_TAG
	{
		MESSENGER_ERROR_CODE_SENDER_CLOSED_UNEXPECTEDLY,
		MESSENGER_ERROR_CODE_RECEIVER_CLOSED_UNEXPECTEDLY
	} MESSENGER_ERROR_CODE;

	typedef enum MESSENGER_SEND_RESULT_TAG
	{
		MESSENGER_SEND_RESULT_SUCCESS,
		MESSENGER_SEND_RESULT_ERROR
	} MESSENGER_SEND_RESULT;

	typedef void (*ON_MESSENGER_ERROR_CALLBACK)(MESSENGER_ERROR_CODE code, void* context);
	typedef void (*ON_MESSAGE_SEND_COMPLETE)(MESSENGER_SEND_RESULT send_result, void* context);
	typedef void(*ON_MESSAGE_RECEIVED)(IOTHUB_MESSAGE_HANDLE message, void* context);

	typedef struct MESSENGER_CONFIG_TAG
	{
		char* device_id;
		
		char* iothub_host_fqdn;
		
		PDLIST_ENTRY wait_to_send_list;
		
		ON_MESSAGE_SEND_COMPLETE on_event_send_completed_callback;

		void* on_event_send_completed_context;

		ON_MESSENGER_ERROR_CALLBACK on_error_callback;
		
		void* on_error_context;
	} MESSENGER_CONFIG;

	typedef struct MESSENGER_STATE* MESSENGER_HANDLE;

	extern MESSENGER_HANDLE messenger_create(const MESSENGER_CONFIG* messenger_config);

	extern int messenger_subscribe_for_messages(MESSENGER_HANDLE messenger_handle, ON_MESSAGE_RECEIVED on_message_received_callback, void* context);

	extern int messenger_unsubscribe_for_messages(MESSENGER_HANDLE messenger_handle);

	extern int messenger_start(MESSENGER_HANDLE messenger_handle, SESSION_HANDLE session_handle); 

	extern int messenger_stop(MESSENGER_HANDLE messenger_handle);

	extern void messenger_do_work(MESSENGER_HANDLE messenger_handle);

	extern void messenger_destroy(MESSENGER_HANDLE messenger_handle);

#ifdef __cplusplus
}
#endif

#endif /*IOTHUBTRANSPORTAMQP_MESSENGER_H*/
