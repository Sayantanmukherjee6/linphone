/*
 * client-group-chat-room.h
 * Copyright (C) 2010-2017 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _CLIENT_GROUP_CHAT_ROOM_H_
#define _CLIENT_GROUP_CHAT_ROOM_H_

#include "chat/chat-room/chat-room.h"
#include "conference/remote-conference.h"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class ClientGroupChatRoomPrivate;

class LINPHONE_PUBLIC ClientGroupChatRoom : public ChatRoom, public RemoteConference {
public:
	// TODO: Make me private.
	ClientGroupChatRoom (
		const std::shared_ptr<Core> &core,
		const Address &me,
		const std::string &uri,
		const std::string &subject
	);

	CapabilitiesMask getCapabilities () const override;

	/* ConferenceInterface */
	void addParticipant (const Address &addr, const CallSessionParams *params, bool hasMedia) override;
	void addParticipants (const std::list<Address> &addresses, const CallSessionParams *params, bool hasMedia) override;
	bool canHandleParticipants () const override;
	std::shared_ptr<Participant> findParticipant (const Address &addr) const override;
	const Address &getConferenceAddress () const override;
	int getNbParticipants () const override;
	std::list<std::shared_ptr<Participant>> getParticipants () const override;
	const std::string &getSubject () const override;
	void join () override;
	void leave () override;
	void removeParticipant (const std::shared_ptr<const Participant> &participant) override;
	void removeParticipants (const std::list<std::shared_ptr<Participant>> &participants) override;
	void setParticipantAdminStatus (std::shared_ptr<Participant> &participant, bool isAdmin) override;
	void setSubject (const std::string &subject) override;

protected:
	void onChatMessageReceived (const std::shared_ptr<ChatMessage> &msg) override;

private:
	/* ConferenceListener */
	void onConferenceCreated (const Address &addr) override;
	void onConferenceTerminated (const Address &addr) override;
	void onParticipantAdded (std::shared_ptr<ConferenceParticipantEvent> event) override;
	void onParticipantRemoved (std::shared_ptr<ConferenceParticipantEvent> event) override;
	void onParticipantSetAdmin (std::shared_ptr<ConferenceParticipantEvent> event) override;
	void onSubjectChanged (std::shared_ptr<ConferenceSubjectEvent> event) override;
	void onParticipantDeviceAdded (std::shared_ptr<ConferenceParticipantDeviceEvent> event) override;
	void onParticipantDeviceRemoved (std::shared_ptr<ConferenceParticipantDeviceEvent> event) override;

private:
	/* CallSessionListener */
	void onCallSessionSetReleased (const std::shared_ptr<const CallSession> &session) override;
	void onCallSessionStateChanged (const std::shared_ptr<const CallSession> &session, LinphoneCallState state, const std::string &message) override;

private:
	L_DECLARE_PRIVATE(ClientGroupChatRoom);
	L_DISABLE_COPY(ClientGroupChatRoom);
};

LINPHONE_END_NAMESPACE

#endif // ifndef _CLIENT_GROUP_CHAT_ROOM_H_