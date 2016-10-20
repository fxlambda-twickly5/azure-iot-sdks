// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdint.h>
#include <time.h>
#include <limits.h>

#include "iothubtransportamqp_messenger.h"
#include "azure_c_shared_utility\strings.h"
#include "azure_uamqp_c\link.h"
#include "azure_uamqp_c\message_sender.h"
#include "azure_uamqp_c\message_receiver.h"


#define RESULT_OK 0

#define DEFAULT_INCOMING_WINDOW_SIZE UINT_MAX
#define DEFAULT_OUTGOING_WINDOW_SIZE 100
#define MESSAGE_RECEIVER_LINK_NAME "receiver-link"
#define MESSAGE_RECEIVER_TARGET_ADDRESS "ingress-rx"
#define MESSAGE_RECEIVER_MAX_LINK_SIZE 65536
#define MESSAGE_SENDER_LINK_NAME "sender-link"
#define MESSAGE_SENDER_SOURCE_ADDRESS "ingress"
#define MESSAGE_SENDER_MAX_LINK_SIZE UINT64_MAX


typedef struct MESSENGER_STATE_TAG
{
	// ID of the device this messenger server to.
	STRING_HANDLE device_id;
	
	// FQDN of the IoT Hub.
	STRING_HANDLE iothub_host_fqdn;

	// Handle to SESSION instance used to create the message_sender and message_receiver.
	SESSION_HANDLE session_handle;

	// AMQP link used by the event sender.
	LINK_HANDLE sender_link;
	// uAMQP event sender.
	MESSAGE_SENDER_HANDLE message_sender;

	// AMQP link used by the message receiver.
	LINK_HANDLE receiver_link;
	// uAMQP message receiver.
	MESSAGE_RECEIVER_HANDLE message_receiver;
	// List with events still pending to be sent. It is provided by the upper layer.

	// Internal flag that controls if messages should be received or not.
	bool receive_messages;
	
	// List with events still pending to be sent. It is provided by the upper layer.
	PDLIST_ENTRY wait_to_send_list;
	// Internal list with the items currently being processed/sent through uAMQP.
	DLIST_ENTRY in_progress_list;
} MESSENGER_STATE;


MESSENGER_HANDLE messenger_create(const MESSENGER_CONFIG* messenger_config)
{
	MESSENGER_HANDLE result;

	return result;
}

int messenger_subscribe_for_messages(MESSENGER_HANDLE messenger_handle, ON_MESSAGE_RECEIVED on_message_received_callback, void* context)
{
	int result;

	return result;
}

int messenger_unsubscribe_for_messages(MESSENGER_HANDLE messenger_handle)
{
	int result;

	return result;
}

int messenger_start(MESSENGER_HANDLE messenger_handle, SESSION_HANDLE session_handle)
{
	int result;

	return result;
}

int messenger_stop(MESSENGER_HANDLE messenger_handle)
{
	int result;

	return result;
}

void messenger_do_work(MESSENGER_HANDLE messenger_handle)
{

}

void messenger_destroy(MESSENGER_HANDLE messenger_handle)
{

}