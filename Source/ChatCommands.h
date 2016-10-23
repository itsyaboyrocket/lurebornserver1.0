#pragma once
#include "AccountsDB.h"

#include <vector>
#include <unordered_map>

class ChatCommandHandler{
public:
	virtual void handleCommand(SessionInfo *s, std::vector<std::wstring> * params) = 0;
	virtual std::vector<std::wstring> getCommandNames() = 0;
	virtual std::wstring getDescription() = 0;
	virtual std::wstring getShortDescription() = 0;
	virtual std::wstring getSyntax() = 0;
};

class ChatCommandManager{
	static std::vector<ChatCommandHandler *> ChatCommandHandlers;
	static std::unordered_map<std::wstring, ChatCommandHandler *> ChatCommands;
public:
	static void registerCommands(ChatCommandHandler * CommandHandler);
	static void handleCommand(std::wstring message, SessionInfo *s);
};

class FlightCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class TeleportCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class WhisperCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class TestmapCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class SwitchCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class ItemsCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class AddItemCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class PositionCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class ClientCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class AttributeCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class PermissionCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class AnnouncementCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class AdminCommandHandler : public ChatCommandHandler{
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class KickCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class CloakCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class SpawnCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class RemoveCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class MissionCommandHandler : public ChatCommandHandler {
public:
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class DropCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class RotationCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class FlagCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class PlayAnimationCommandHandler : public ChatCommandHandler {
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class SmashCommandHandler : public ChatCommandHandler {
public:
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class MacroCommandHandler : public ChatCommandHandler {
public:
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};

class TestCommandHandler : public ChatCommandHandler {
public:
	void handleCommand(SessionInfo *s, std::vector<std::wstring> * params);
	std::vector<std::wstring> getCommandNames();
	std::wstring getDescription();
	std::wstring getShortDescription();
	std::wstring getSyntax();
};