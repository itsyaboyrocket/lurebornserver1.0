#include "CharactersDB.h"

long long CharactersTable::getObjidFromCharacter(std::string name){
	std::stringstream iq;
	iq << "SELECT `objectID` FROM `characters` WHERE `name` = '" << name << "';";
	std::string qrs = iq.str();
	auto iqr = Database::Query(qrs);
	if (mysql_num_rows(iqr) > 0){
		auto ir = mysql_fetch_row(iqr);
		long long objid = std::stoll(ir[0]);
		return objid;
	}
	else{
		return -1; //-1 as return value
	}
}

unsigned int CharactersTable::getAccountFromObjid(long long objid){
	auto qr = Database::Query("SELECT `accountID` FROM `characters` WHERE `objectID` = '" + std::to_string(objid) + "' LIMIT 1;");
	if (mysql_num_rows(qr) == 0) {
		return 0;
	}
	auto r = mysql_fetch_row(qr);
	return std::stoi(r[0]);
}

std::vector<long long> CharactersTable::getCharacters(unsigned int accountid){
	std::vector<long long> chars;
	auto qr = Database::Query("SELECT `id`, `objectID` FROM `characters` WHERE `accountID` = " + std::to_string(accountid) + " LIMIT 4"); // Load chars from MySQL DB
	MYSQL_ROW row;
	chars.reserve(4);
	if (qr == NULL){
		return chars;
		Logger::logError("CHDB", "MYSQL", "getting characters", mysql_error(Database::getConnection()));
	}
	while (row = mysql_fetch_row(qr)) {
		std::stringstream s(row[1]);
		long long cid;
		s >> cid;
		unsigned short id = std::stoi(row[0]);
		chars.push_back(cid);
	}
	return chars;
}

/*ListCharacterInfo CharactersTable::getCharacterInfo(CharacterOwner owner){
std::stringstream qrs;
qrs << "SELECT ";
qrs << "`objectID`, `name`, `unapprovedName`, `nameRejected`, `freeToPlay`, ";
qrs << "`shirtColor`, `shirtStyle`, `pantsColor`, `hairStyle`, `hairColor`, `lh`, `rh`, `eyebrows`, `eyes`, `mouth`, ";
qrs << "`lastZoneId`, `mapInstance`, `mapClone`, `x`, `y`, `z`, `uScore`, `level ";
qrs << "FROM `characters` WHERE `id` = '" << std::to_string(owner.charIndex) << "' AND `accountID` = '" << std::to_string(owner.accountid) << "';";
std::string qrss = qrs.str();
auto qr = Database::Query(qrss);
return CharactersTable::getCharacterInfo(qr);
}*/

ListCharacterInfo CharactersTable::getCharacterInfo(long long objid){
	std::stringstream qrs;
	qrs << "SELECT ";
	qrs << "`accountID`, `objectID`, `name`, `unapprovedName`, `nameRejected`, `freeToPlay`, `gmlevel`, "; //0-6
	qrs << "`shirtColor`, `shirtStyle`, `pantsColor`, `hairStyle`, `hairColor`, `lh`, `rh`, `eyebrows`, `eyes`, `mouth`, "; //7-16
	qrs << "`lastZoneId`, `mapInstance`, `mapClone`, `x`, `y`, `z`, `uScore`, `level`, `currency`, `reputation`, "; //17-26
	qrs << "`invSizeTab0`, `invSizeTab1`, `invSizeTab2`, `invSizeTab3`, `cloaked` "; //27-31
	qrs << "FROM `characters` WHERE `objectID` = '" << std::to_string(objid) << "';";
	std::string qrss = qrs.str();
	auto qr = Database::Query(qrss);
	if (qr == NULL){
		Logger::logError("CHDB", "MYSQL", "getting charinfo by objid", mysql_error(Database::getConnection()));
		return ListCharacterInfo();
	}
	return CharactersTable::getCharacterInfo(qr);
}

ListCharacterInfo CharactersTable::getCharacterInfo(std::string name){
	std::stringstream qrs;
	qrs << "SELECT ";
	qrs << "`accountID`, `objectID`, `name`, `unapprovedName`, `nameRejected`, `freeToPlay`, `gmlevel`, "; //0-6
	qrs << "`shirtColor`, `shirtStyle`, `pantsColor`, `hairStyle`, `hairColor`, `lh`, `rh`, `eyebrows`, `eyes`, `mouth`, "; //7-16
	qrs << "`lastZoneId`, `mapInstance`, `mapClone`, `x`, `y`, `z`, `uScore`, `level`, `currency`, `reputation`, "; //17-26
	qrs << "`invSizeTab0`, `invSizeTab1`, `invSizeTab2`, `invSizeTab3`, `cloaked` "; //27-31
	qrs << "FROM `characters` WHERE `name` = '" << name << "';";
	std::string qrss = qrs.str();
	auto qr = Database::Query(qrss);
	return CharactersTable::getCharacterInfo(qr);
}

ListCharacterInfo CharactersTable::getCharacterInfo(MYSQL_RES *res){
	ListCharacterInfo i;
	if (mysql_num_rows(res) == 0) {
		i.info.objid = 0;
		return i;
	}
	else {
		//Info
		auto r = mysql_fetch_row(res);
		i.info.accountid = std::stoul(r[0]);
		i.info.objid = std::stoll(r[1]);
		i.info.name = r[2];
		i.info.unapprovedName = r[3];
		i.info.nameRejected = (std::stoi(r[4]) == 1);
		i.info.isFreeToPlay = (std::stoi(r[5]) == 1);
		i.info.gmlevel = std::stoi(r[6]);
		i.info.uscore = std::stoi(r[23]);
		i.info.level = std::stoi(r[24]);
		i.info.cloaked = (std::stoi(r[30]) == 1);
		i.info.currency = std::stoi(r[25]);
		i.info.reputation = std::stoi(r[26]);
		i.info.inventorySize = std::vector<int>{ std::stoi(r[27]),std::stoi(r[28]),std::stoi(r[29]),std::stoi(r[30]) };
		//Style
		i.style.shirtColor = std::stoul(r[7]);
		i.style.shirtStyle = std::stoul(r[8]);
		i.style.pantsColor = std::stoul(r[9]);
		i.style.hairStyle = std::stoul(r[10]);
		i.style.hairColor = std::stoul(r[11]);
		i.style.lh = std::stoul(r[12]);
		i.style.rh = std::stoul(r[13]);
		i.style.eyebrows = std::stoul(r[14]);
		i.style.eyes = std::stoul(r[15]);
		i.style.mouth = std::stoul(r[16]);
		//Place
		i.lastPlace.zoneID = std::stoi(r[17]);
		i.lastPlace.mapInstance = std::stoi(r[18]);
		i.lastPlace.mapClone = std::stoul(r[19]);
		i.lastPlace.x = std::stof(r[20]);
		i.lastPlace.y = std::stof(r[21]);
		i.lastPlace.z = std::stof(r[22]);
	}
	return i;
}

bool CharactersTable::setCharactersPlace(long long objid, WorldPlace place){
	std::stringstream qr;
	qr << "UPDATE `characters` SET ";
	qr << "`lastZoneId` = '" << std::to_string(place.zoneID);
	qr << "', `mapInstance` = '" << std::to_string(place.mapInstance);
	qr << "', `mapClone` = '" << std::to_string(place.mapClone);
	qr << "', `x` = '" << std::to_string(place.x);
	qr << "', `y` = '" << std::to_string(place.y);
	qr << "', `z` = '" << std::to_string(place.z);
	/*qr << "', `rotX` = '" << std::to_string(place.rotX);
	qr << "', `rotY` = '" << std::to_string(place.rotY);
	qr << "', `rotZ` = '" << std::to_string(place.rotZ);
	qr << "', `rotW` = '" << std::to_string(place.rotW);*/
	qr << "' WHERE `objectID` = '" << std::to_string(objid) << "';";
	std::string qrs = qr.str();
	/*MYSQL_RES *a = Database::Query(qrs);
	if (a == NULL){
		Logger::log("SQL","ERROR", Database::getConnection()->status());
		return false;
	}
	return true;*/

	Database::Query(qrs);
	return true;
}

void CharactersTable::deleteCharacter(long long objid){
	std::stringstream query;
	query << "DELETE FROM `characters` WHERE `objectID` = '" << std::to_string(objid) << "';";
	Database::Query(query.str());
}

std::vector<unsigned char> CharactersTable::getCharacterIndices(unsigned int accountid){
	std::vector<unsigned char> chars;
	auto qr = Database::Query("SELECT `id`, `objectID` FROM `characters` WHERE `accountID` = " + std::to_string(accountid) + " LIMIT 4"); // Load chars from MySQL DB
	MYSQL_ROW row;
	while (row = mysql_fetch_row(qr)) {
		unsigned char id = std::stoi(row[0]);
		chars.push_back(id);
	}
	return chars;
}

long long CharactersTable::add(CharacterStyle style, unsigned int accountid, CharacterInfo names){
	std::stringstream query2;
	query2 << "INSERT INTO `characters` (`accountID`, `objectID`, `name`, `unapprovedName`, `nameRejected`, `freeToPlay`, ";
	query2 << "`shirtColor`, `shirtStyle`, `pantsColor`, `hairStyle`, `hairColor`, `lh`, `rh`, `eyebrows`, `eyes`, `mouth`, `lastZoneId`) ";
	query2 << "VALUES('" << std::to_string(accountid) << "', NULL, '" << names.name << "', '" << names.unapprovedName << "', '0', '0', '";
	query2 << std::to_string(style.shirtColor) << "', '" << std::to_string(style.shirtStyle) << "', '";
	query2 << std::to_string(style.pantsColor) << "', '" << std::to_string(style.hairStyle) << "', '" << std::to_string(style.hairColor) << "', '";
	query2 << std::to_string(style.lh) << "', '" << std::to_string(style.rh) << "', '" << std::to_string(style.eyebrows) << "', '";
	query2 << std::to_string(style.eyes) << "', '" << std::to_string(style.mouth) << "', '1000'); ";
	Database::Query(query2.str());
	return std::stoll(mysql_fetch_row(Database::Query("SELECT `objectID` from `characters` WHERE `name`="+names.name))[0]);
}

bool CharactersTable::unapprovedNameExists(std::string unapprovedname){
	auto qr2 = Database::Query("SELECT `unapprovedName` FROM `characters` WHERE `unapprovedName` = '" + unapprovedname + "';");
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return false;
	else
		return true;
}

void CharactersTable::setGMlevel(long long objid, unsigned short newLevel){
	std::stringstream str;
	str << "UPDATE `characters` SET `gmlevel` = '" << std::to_string(newLevel) << "' WHERE `objectID` = '" << std::to_string(objid) << "'";
	Database::Query(str.str());
}

void CharactersTable::setCloaked(long long charid, bool value){
	std::stringstream str;
	str << "UPDATE `characters` SET `cloaked` = '" << (value?"1":"0") << "' WHERE `objectID` = '" << std::to_string(charid) << "'";
	Database::Query(str.str());
}

void CharactersTable::setUScore(long long objid, unsigned int score){
	std::stringstream str;
	str << "UPDATE `characters` SET `uScore` = '" << std::to_string(score) << "' WHERE `objectID` = '" << std::to_string(objid) << "'";
	Database::Query(str.str());
}

std::string CharactersTable::getName(){
	return "characters";
}

void CharactersTable::mapTable(std::unordered_map<std::string, compare<ColData *> *> * data){
	Database::addColToMap(data, "id", new ColData("bigint(20) unsigned", false, "", "0", ""));
	Database::addColToMap(data, "accountID", new ColData("int(10) unsigned", false, "", "NULL", ""));
	Database::addColToMap(data, "objectID", new ColData("bigint(20)", false, "PRI", "NULL", "auto_increment"));
	Database::addColToMap(data, "name", new ColData("varchar(25)", false, "", "NULL", ""));
	Database::addColToMap(data, "unapprovedName", new ColData("varchar(66)", false, "", "NULL", ""));
	Database::addColToMap(data, "nameRejected", new ColData("tinyint(4)", false, "", "0", ""));
	Database::addColToMap(data, "freeToPlay", new ColData("tinyint(4)", false, "", "0", ""));
	Database::addColToMap(data, "gmlevel", new ColData("mediumint(9)", false, "", "0", ""));
	Database::addColToMap(data, "shirtColor", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "shirtStyle", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "pantsColor", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "hairStyle", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "hairColor", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "lh", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "rh", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "eyebrows", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "eyes", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "mouth", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "lastZoneId", new ColData("int(11)", false, "", "NULL", ""));
	Database::addColToMap(data, "mapInstance", new ColData("int(11)", false, "", "NULL", ""));
	Database::addColToMap(data, "mapClone", new ColData("int(11)", false, "", "NULL", ""));
	Database::addColToMap(data, "level", new ColData("int(3)", false, "", "1", ""));
	Database::addColToMap(data, "uScore", new ColData("int(32)", false, "", "0", ""));
	Database::addColToMap(data, "invSizeTab0", new ColData("int(5)", false, "", "20", ""));
	Database::addColToMap(data, "invSizeTab1", new ColData("int(5)", false, "", "20", ""));
	Database::addColToMap(data, "invSizeTab2", new ColData("int(5)", false, "", "20", ""));
	Database::addColToMap(data, "invSizeTab3", new ColData("int(5)", false, "", "20", ""));
}

void CharactersTable::UpgradeTable() {
	if (!Database::columnExists("characters", "cloaked"))
		Database::Query("ALTER TABLE `characters` ADD `cloaked` INT(1) NOT NULL DEFAULT '0' AFTER `gmlevel`;");
	if (!Database::columnExists("characters", "invSizeTab0"))
		Database::Query("ALTER TABLE `characters` ADD `invSizeTab0` INT(5) NOT NULL DEFAULT '20';");
	if (!Database::columnExists("characters", "invSizeTab1"))
		Database::Query("ALTER TABLE `characters` ADD `invSizeTab1` INT(5) NOT NULL DEFAULT '20';");
	if (!Database::columnExists("characters", "invSizeTab2"))
		Database::Query("ALTER TABLE `characters` ADD `invSizeTab2` INT(5) NOT NULL DEFAULT '20';");
	if (!Database::columnExists("characters", "invSizeTab3"))
		Database::Query("ALTER TABLE `characters` ADD `invSizeTab3` INT(5) NOT NULL DEFAULT '20';");
}

void FriendsTable::requestFriend(long long sender, long long reciever){
	std::stringstream str;
	str << "INSERT INTO `friends` (`id`, `charida`, `charidb`) VALUES( NULL, '" << sender << "', '" << reciever << "');";
	Database::Query(str.str());
}

void FriendsTable::requestBestFriend(long long sender, long long reciever){
	std::stringstream str;
	str << "UPDATE `friends` SET `status` = 'BEST_FRIEND_REQUEST', ";
	str << "`charida` = '" << std::to_string(sender) << "', ";
	str << "`charidb` = '" << std::to_string(reciever) << "' ";
	str << "WHERE (" << "`charida` = '" << std::to_string(sender) << "' AND `charidb` = '" << std::to_string(reciever) << "') ";
	str << "OR  (" << "`charidb` = '" << std::to_string(sender) << "' AND `charida` = '" << std::to_string(reciever) << "');";
	Database::Query(str.str());
}

//This query ONLY regards the status in one direction, meaning it is only useful if the requester is known
std::string FriendsTable::getRequestStatus(long long sender, long long reciever){
	auto qr = Database::Query("SELECT `status` FROM `friends` WHERE `charida` = '" + std::to_string(sender) + "' AND `charidb` = '" + std::to_string(reciever) + "';");
	if (mysql_num_rows(qr) == 0 || mysql_num_rows(qr) == NULL){
		return "INVALID";
	}
	else{
		auto row = mysql_fetch_row(qr);
		return row[0];
	}
}

std::string FriendsTable::getFriendsStatus(long long charidx, long long charidy){
	std::stringstream str;
	str << "SELECT `status` FROM `friends` ";
	str << "WHERE (" << "`charida` = '" << std::to_string(charidx) << "' AND `charidb` = '" << std::to_string(charidy) << "') ";
	str << "OR  (" << "`charidb` = '" << std::to_string(charidx) << "' AND `charida` = '" << std::to_string(charidy) << "');";
	auto qr = Database::Query(str.str());
	if (mysql_num_rows(qr) == 0 || mysql_num_rows(qr) == NULL){
		return "INVALID";
	}
	else{
		auto row = mysql_fetch_row(qr);
		return row[0];
	}
}

std::vector<long long> FriendsTable::getFriends(long long charobjid){
	std::string qr = "SELECT `charida`, `charidb` FROM `friends` WHERE (`charida` = '" + std::to_string(charobjid) + "' OR `charidb` = '" + std::to_string(charobjid) + "') AND `status` IN ('FRIENDS', 'BEST_FRIEND_REQUEST', 'ACCEPTED');";
	auto qr2 = Database::Query(qr);
	std::vector<long long> friends;
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return friends;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		friends.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			long long chara = std::stoll(row[0]);
			long long charb = std::stoll(row[1]);
			long long fr = 0;
			if (chara == charobjid){
				fr = charb;
			}
			else{
				fr = chara;
			}
			friends.push_back(fr);
		}
		return friends;
	}
}

std::vector<long long> FriendsTable::getBestFriends(long long charobjid){
	std::string qr = "SELECT `charida`, `charidb` FROM `friends` WHERE (`charida` = '" + std::to_string(charobjid) + "' OR `charidb` = '" + std::to_string(charobjid) + "') AND `status` IN ('BEST_FRIENDS', 'BEST_FRIENDS_ACCEPTED');";
	auto qr2 = Database::Query(qr);
	std::vector<long long> friends;
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return friends;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		friends.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			long long chara = std::stoll(row[0]);
			long long charb = std::stoll(row[1]);
			long long fr = 0;
			if (chara == charobjid){
				fr = charb;
			}
			else{
				fr = chara;
			}
			friends.push_back(fr);
		}
		return friends;
	}
}

std::vector<std::pair<long long, std::string>> FriendsTable::getFriendResponses(long long charobjid){
	std::string qr = "SELECT `charidb`, `status` FROM `friends` WHERE `charida` = '" + std::to_string(charobjid) + "' AND `status` in ('ACCEPTED', 'DECLINED');";
	auto qr2 = Database::Query(qr);
	std::vector<std::pair<long long, std::string>> requests;
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return requests;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		requests.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			long long charb = std::stoll(row[0]);
			std::string status = row[1];
			requests.push_back(std::make_pair(charb, status));
		}
		return requests;
	}
}

std::vector<long long> FriendsTable::getFriendRequests(long long charobjid){
	std::string qr = "SELECT `charida` FROM `friends` WHERE `charidb` = '" + std::to_string(charobjid) + "' AND `status` = 'REQUEST';";
	auto qr2 = Database::Query(qr);
	std::vector<long long> requests;
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return requests;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		requests.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			long long chara = std::stoll(row[0]);
			requests.push_back(chara);
		}
		return requests;
	}
}

std::vector<long long> FriendsTable::getBestFriendRequests(long long charobjid){
	std::string qr = "SELECT `charida` FROM `friends` WHERE `charidb` = '" + std::to_string(charobjid) + "' AND `status` = 'BEST_FRIEND_REQUEST';";
	auto qr2 = Database::Query(qr);
	std::vector<long long> requests;
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return requests;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		requests.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			long long chara = std::stoll(row[0]);
			requests.push_back(chara);
		}
		return requests;
	}
}

void FriendsTable::setRequestStatus(long long charida, long long charidb, const std::string& status){
	std::stringstream str;
	str << "UPDATE `friends` SET `status` = '" << status << "' ";
	str << "WHERE " << "`charida` = '" << std::to_string(charida) << "' AND `charidb` = '" << std::to_string(charidb) << "';";
	Database::Query(str.str());
}

void FriendsTable::accept(long long requester, long long accepter){
	FriendsTable::setRequestStatus(requester, accepter, "ACCEPTED");

}

void FriendsTable::decline(long long requester, long long accepter){
	FriendsTable::setRequestStatus(requester, accepter, "DECLINED");
}

std::string FriendsTable::getName(){
	return "friends";
}

void FriendsTable::mapTable(std::unordered_map<std::string, compare<ColData *> *> * data){
	Database::addColToMap(data, "id", new ColData("int(11)", false, "PRI", "NULL", "auto_increment"));
	Database::addColToMap(data, "charida", new ColData("bigint(20)", false, "", "NULL", ""));
	Database::addColToMap(data, "charidb", new ColData("bigint(20)", false, "", "NULL", ""));
	Database::addColToMap(data, "status", new ColData("enum('REQUEST','ACCEPTED','DECLINED','FRIENDS','BEST_FRIEND_REQUEST','BEST_FRIENDS')", false, "", "REQUEST", ""));
}

std::vector<MISSION_DATA> MissionsTable::getMissions(long long charid){
	std::string qr = "SELECT `missionid`, `count`, UNIX_TIMESTAMP(`time`), `status` FROM `missions` WHERE `character` = '" + std::to_string(charid) + "';";
	auto qr2 = Database::Query(qr);
	std::vector<MISSION_DATA> missions;
	if (qr2 == NULL){
		Logger::logError("CHDB", "MYSQL", "getting mission", mysql_error(Database::getConnection()));
	}
	if (qr2 == NULL || mysql_num_rows(qr2) == 0)
		return missions;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		missions.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			MISSION_DATA m;
			m.missionid = std::stoi(row[0]);
			m.missioncount = std::stoi(row[1]);
			m.timestamp = std::stoi(row[2]);
			m.missionStatus = std::stoi(row[3]);
			missions.push_back(m);
		}
		return missions;
	}
}

MISSION_DATA MissionsTable::getMissionById(long long charid, int misID) {
	MISSION_DATA m;
	m.missionid = -1;
	std::string qr = "SELECT `count`, UNIX_TIMESTAMP(`time`), `status` FROM `missions` WHERE `character` = '" + std::to_string(charid) +"' AND `missionid` = "+std::to_string(misID)+" LIMIT 1;";
	auto qr2 = Database::Query(qr);
	if (qr2 == NULL || !(mysql_num_rows(qr2) > 0)) {
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			m.missionid = misID;
			m.missioncount = std::stoi(row[0]);
			m.timestamp = std::stoi(row[1]);
			m.missionStatus = std::stoi(row[2]);
		}
	}
	return m;
}

bool MissionsTable::haveMission(long long charid, int misID) {
	int mid = MissionsTable::getMissionById(charid, misID).missionid;
	Logger::log("CHDB", "MSDB", "HaveMission: " + (mid<0)?"NO":"YES");
	return !(mid <0);
}

void MissionsTable::addMission(long long charid, int misID) {
	if (!MissionsTable::haveMission(charid, misID)) {
		std::stringstream qs;
		qs << "INSERT INTO `missions`(`missionid`,`count`,`status`,`character`) ";
		qs << "VALUES (" << misID << ",0," << std::to_string(int(MISSION_AVAILABLE)) << "," << charid << ");";
		auto q=Database::Query(qs.str());
	}
}

std::string MissionsTable::getName(){
	return "missions";
}

void MissionsTable::mapTable(std::unordered_map<std::string, compare<ColData *> *> * data){
	Database::addColToMap(data, "id", new ColData("bigint(20)", false, "PRI", "NULL", "auto_increment"));
	Database::addColToMap(data, "character", new ColData("bigint(20)", false, "", "NULL", ""));
	Database::addColToMap(data, "missionid", new ColData("int(11)", false, "", "NULL", ""));
	Database::addColToMap(data, "time", new ColData("timestamp", false, "", "CURRENT_TIMESTAMP", "on update CURRENT_TIMESTAMP"));
	Database::addColToMap(data, "count", new ColData("smallint(6)", false, "", "1", ""));
}

void MailsTable::addMail(MailData data){
	std::stringstream query2;
	query2 << "INSERT INTO `mails` (`sender`, `recipient_id`, `subject`, `text`, `attachment`, `attachment_count`) ";
	query2 << "VALUES('" << data.sender << "', '" << std::to_string(data.recipient) << "', '";
	query2 << data.subject << "', '" << data.text << "', '" << std::to_string(data.attachment) << "', '" << std::to_string(data.attachment_count) << "'); ";
	auto a = Database::Query(query2.str());
	if (a == NULL){
		Logger::logError("CHDB", "MYSQL", "adding mail", mysql_error(Database::getConnection()));
	}
}

void MailsTable::setIsRead(long long mailid){
	std::stringstream str;
	str << "UPDATE `mails` SET `is_read` = '1' ";
	str << "WHERE " << "`id` = '" << std::to_string(mailid) << "';";
	Database::Query(str.str());
}

std::vector<MailData> MailsTable::getMails(long long charid){
	std::string qr = "SELECT `id`, `subject`, `text`, `sender`, `attachment`, `attachment_count`, UNIX_TIMESTAMP(`sent_time`), `is_read` FROM `mails` WHERE `recipient_id` = '" + std::to_string(charid) + "';";
	auto qr2 = Database::Query(qr);
	std::vector<MailData> mails;
	if (qr2 == NULL){
		Logger::logError("CHDB", "MYSQL", "getting mails", mysql_error(Database::getConnection()));
		return mails;
	}
	if (mysql_num_rows(qr2) == 0 || mysql_num_rows(qr2) == NULL)
		return mails;
	else{
		unsigned int numrows = (unsigned int)mysql_num_rows(qr2);
		mails.reserve(numrows);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr2)) {
			MailData mail;
			mail.id = std::stoll(row[0]);
			mail.subject = row[1];
			mail.text = row[2];
			mail.sender = row[3];
			mail.attachment = std::stoll(row[4]);
			mail.attachment_count = std::stoi(row[5]);
			mail.sent_time = std::stoi(row[6]);
			unsigned char readN = std::stoi(row[7]);
			if (readN == 1) mail.read = true; else mail.read = false;
			mails.push_back(mail);
		}
		return mails;
	}
}

void MailsTable::deleteMail(long long mailid){
	std::stringstream str;
	str << "DELETE FROM `mails` WHERE `id` = '" << std::to_string(mailid) << "';";
	Database::Query(str.str());
}

std::string MailsTable::getName(){
	return "mails";
}

void MailsTable::mapTable(std::unordered_map<std::string, compare<ColData *> *> * data){
	Database::addColToMap(data, "id", new ColData("bigint(20)", false, "PRI", "NULL", "auto_increment"));
	Database::addColToMap(data, "subject", new ColData("text", false, "", "NULL", ""));
	Database::addColToMap(data, "text", new ColData("text", false, "", "NULL", ""));
	Database::addColToMap(data, "sender", new ColData("text", false, "", "NULL", ""));
	Database::addColToMap(data, "recipient_id", new ColData("bigint(20)", false, "", "NULL", ""));
	Database::addColToMap(data, "attachment", new ColData("bigint(20)", false, "", "0", ""));
	Database::addColToMap(data, "attachment_count", new ColData("int(11)", false, "", "0", ""));
	Database::addColToMap(data, "sent_time", new ColData("datetime", false, "", "CURRENT_TIMESTAMP", ""));
	Database::addColToMap(data, "is_read", new ColData("tinyint(1)", false, "", "0", ""));
}

void StatsTable::mapTable(std::unordered_map<std::string, compare<ColData *> *> * data) {
	//TODO: Add DatabaseTables
}

std::string StatsTable::getName() {return "statistics";}

PLAYER_STATS StatsTable::getPlayerStats(long long charid, bool secondTry) {//secondTry to prevent infinity loop
	PLAYER_STATS ps;
	auto qr = Database::Query("SELECT * FROM `statistics` WHERE `player`=" + std::to_string(charid));
	if (qr != NULL &&mysql_num_rows(qr) > 0) {
		MYSQL_ROW row;
		while (row = mysql_fetch_row(qr)) {
			ps.CurrencyCollected = std::stoull(row[1]);
			ps.BricksCollected = std::stoull(row[2]);
			ps.SmashablesSmashed = std::stoull(row[3]);
			ps.QuickBuildsCompleted = std::stoull(row[4]);
			ps.EnemiesSmashed = std::stoull(row[5]);
			ps.RocketsUsed = std::stoull(row[6]);
			ps.MissionsCompleted = std::stoull(row[7]);
			ps.PetsTamed = std::stoull(row[8]);
			ps.ImaginationPowerupsCollected = std::stoull(row[9]);
			ps.LifePowerupsCollected = std::stoull(row[10]);
			ps.ArmorPowerupsCollected = std::stoull(row[11]);
			ps.DistanceTraveled = std::stoull(row[12]);
			ps.Smashed = std::stoull(row[13]);
			ps.DamageTaken = std::stoull(row[14]);
			ps.DamageHealed = std::stoull(row[15]);
			ps.ArmorRepaired = std::stoull(row[16]);
			ps.ImaginationRestored = std::stoull(row[17]);
			ps.ImaginationUsed = std::stoull(row[18]);
			ps.DistanceDriven = std::stoull(row[19]);
			ps.AirborneInRacecar = std::stoull(row[20]);
			ps.RacingImaginationPowerupsCollected = std::stoull(row[21]);
			ps.RacingImaginationCratesSmashed = std::stoull(row[22]);
			ps.RaceCarBoostActivated = std::stoull(row[23]);
			ps.WrecksInRaceCar = std::stoull(row[24]);
			ps.RacingSmashablesSmashed = std::stoull(row[25]);
			ps.RacesFinished = std::stoull(row[26]);
			ps.Place1RacesFinishes = std::stoull(row[27]);
		}
	}
	else {
		if (!secondTry) {
			Database::Query("INSERT INTO `statistics` (player) VALUES(" + std::to_string(charid) + ")");
			ps = getPlayerStats(charid, true);
		}
	}
	return ps;
}