# Introduction #
<pre>
Original ipmsg protocol specification is written in Japanese.<br>
This document was translated by Mr.Kanazawa.<br>
This document is not verified yet.<br>
<br>
----------------------------------------------------------------------<br>
IP Messenger communication protocol (Draft-9)    1996/02/21<br>
Modified 2003/01/14<br>
<br>
H.Shirouzu<br>
shirouzu@h.email.ne.jp<br>
----------------------------------------------------------------------<br>
</pre>
# Details #
<pre>
About IP Messenger<br>
This is a Send/Receive message service using the TCP/UDP Port.<br>
<br>
Characteristics<br>
IP Messenger can be installed in any OS if TCP/IP is used on your machine.<br>
Dynamic member recognition can be done within your network or specified network.<br>
You can exchange messages between all IPMsg members.<br>
<br>
Function description<br>
Use TCP/UDP port(default:2425). See the following descriptions<br>
(Message Send/Receive: UDP, File Send/Receive: TCP)<br>
<br>
1. Command<br>
<br>
1) Command functions (Low 8 bits from command number 32 bits)<br>
<br>
IPMSG_NOOPERATION	No Operation<br>
IPMSG_BR_ENTRY		Entry to service (Start-up with a Broadcast command)<br>
IPMSG_BR_EXIT		Exit from service (End with a Broadcast command)<br>
IPMSG_ANSENTRY		Notify a new entry<br>
IPMSG_BR_ABSENCE	Change absence mode<br>
<br>
IPMSG_BR_ISGETLIST	Search valid sending host members<br>
IPMSG_OKGETLIST		Host list sending notice<br>
IPMSG_GETLIST		Host list sending request<br>
IPMSG_ANSLIST		Host list sending<br>
<br>
IPMSG_SENDMSG		Message transmission<br>
IPMSG_RECVMSG		Message receiving check<br>
<br>
IPMSG_READMSG		Message open notice<br>
IPMSG_DELMSG		Message discarded notice<br>
IPMSG_ANSREADMSG	Message open confirmation notice(added from version-8)<br>
<br>
IPMSG_GETFILEDATA	File Transfer request by TCP<br>
IPMSG_RELEASEFILES	Discard attachment file<br>
IPMSG_GETDIRFILES	Attachment hierarchical file request<br>
<br>
IPMSG_GETINFO		Get IPMSG version info.<br>
IPMSG_SENDINFO		Send IPMSG version info.<br>
<br>
IPMSG_GETABSENCEINFO	Get absence sentence<br>
IPMSG_SENDABSENCEINFO	Send absence sentence<br>
<br>
IPMSG_GETPUBKEY		RSA Public Key Acquisition<br>
IPMSG_ANSPUBKEY		RSA Public Key Response<br>
<br>
2) Option flag (High 24 bits from command number 32 bits)<br>
<br>
IPMSG_ABSENCEOPT	Absence mode(Member recognition command)<br>
IPMSG_SERVEROPT		Server(Reserved)<br>
IPMSG_DIALUPOPT		Send individual member recognition command<br>
<br>
IPMSG_SENDCHECKOPT	Transmission check<br>
IPMSG_SECRETOPT		Sealed message<br>
IPMSG_READCHECKOPT	Sealed message check(added from ver8)<br>
IPMSG_PASSWORDOPT	Lock<br>
IPMSG_BROADCASTOPT	Broadcast message<br>
IPMSG_MULTICASTOPT	Multi-cast(Multiple casts selection)<br>
IPMSG_NEWMUTIOPT	New version multi-cast(reserved)<br>
IPMSG_AUTORETOPT	Automatic response(Ping-pong protection)<br>
IPMSG_NOLOGOPT		No log files<br>
IPMSG_NOADDLISTOPT	Notice to the members outside of BR_ENTRY<br>
<br>
IPMSG_FILEATTACHOPT	File attachment<br>
IPMSG_ENCRYPTOPT	Code<br>
<br>
IPMSG_NOPOPUPOPT	(No longer valid)<br>
IPMSG_RETRYOPT		Re-send flag(Use when acquiring HOSTLIST)<br>
<br>
3) Extended code flag (hex format combination)<br>
<br>
IPMSG_RSA_512<br>
IPMSG_RSA_1024<br>
IPMSG_RSA_2048<br>
IPMSG_RC2_40<br>
IPMSG_RC2_128<br>
IPMSG_RC2_256<br>
IPMSG_BLOWFISH_128<br>
IPMSG_BLOWFISH_256<br>
IPMSG_SIGN_MD5<br>
<br>
4) Extended files for attachment (fileattr low 8 bits)<br>
<br>
IPMSG_FILE_REGULAR<br>
IPMSG_FILE_DIR<br>
IPMSG_FILE_RETPARENT<br>
IPMSG_FILE_SYMLINK<br>
IPMSG_FILE_CDEV<br>
IPMSG_FILE_BDEV<br>
IPMSG_FILE_FIFO<br>
IPMSG_FILE_RESFORK<br>
<br>
5) Attachment file extended attribute(fileattr high 24 bits)<br>
<br>
IPMSG_FILE_RONLYOPT<br>
IPMSG_FILE_HIDDENOPT<br>
IPMSG_FILE_EXHIDDENOPT<br>
IPMSG_FILE_ARCHIVEOPT<br>
IPMSG_FILE_SYSTEMOPT<br>
<br>
6) Extended file attribute for attachment file<br>
<br>
IPMSG_FILE_UID<br>
IPMSG_FILE_USERNAME<br>
IPMSG_FILE_GID<br>
IPMSG_FILE_GROUPNAME<br>
IPMSG_FILE_PERM<br>
IPMSG_FILE_MAJORNO<br>
IPMSG_FILE_MINORNO<br>
IPMSG_FILE_CTIME<br>
IPMSG_FILE_MTIME<br>
IPMSG_FILE_ATIME<br>
IPMSG_FILE_CREATETIME<br>
<br>
IPMSG_FILE_CREATOR<br>
IPMSG_FILE_FILETYPE<br>
IPMSG_FILE_FINDERINFO<br>
<br>
IPMSG_FILE_ACL<br>
IPMSG_FILE_ALIASFNAME<br>
IPMSG_FILE_UNICODEFNAME<br>
<br>
<br>
2.Command format(Use all character strings)<br>
<br>
1) Command(Format version-1)<br>
<br>
Ver(1) : PacketNo : SenderName : SenderHost : CommandNo : AdditionalSection<br>
<br>
2) An example for Message Send/Receive by using the current command format<br>
<br>
"1:100:shirouzu:jupiter:32:Hello"<br>
<br>
<br>
3.Command process overview<br>
<br>
1) Member recognition<br>
<br>
An IPMSG_BR_ENTRY command notifies a new entry to the current<br>
members at start-up.<br>
<br>
All members add the new member to their list after getting a notification message.<br>
An IPMSG_ANSENTRY command sends a message back to the new member.<br>
<br>
The new member gets the current member data by a<br>
IPMSG_ANSENTRY command. All members can communicate as long as an<br>
IP packet exists.<br>
<br>
An IPMSG_BR_ABSENCE command broadcasts absence mode cancel or<br>
nickname change to all members. However, an IPMSG_ANSENTRY command<br>
does not send a message back, which is different from an IPMSG_BR_ENTRY<br>
command.<br>
<br>
IPMSG_BR_ENTRY, IPMSG_ANSENTRY, and IPMSG_BR_ABSENCE commands<br>
use an IPMSG_ABSENCEOPT flag for absence mode. Input a nickname to<br>
additional command.<br>
Add an IPMSG_DIALUPOPT flag for dial-up users who can't be reached by<br>
a broadcast command.  A member recognition command needs to be<br>
sent individually to the members with this optional flag.<br>
<br>
(Extended group)IPMSG_BR_ENTRY and IPMSG_BR_ABSENCE commands<br>
sends a group name by adding the new group name after the current<br>
command format character strings (Input '\0' between the current<br>
command and extended name).<br>
<br>
2) Send/Receive Message<br>
Send Message uses an IPMSG_SENDMSG command that can input a message<br>
in the extended area.<br>
Receive Message sends back an IPMSG_RECVMSG command only<br>
if an IPMSG_SENDCHECKOPT flag is ON. Input the original packet number<br>
to the extended area.<br>
<br>
Broadcast Message Send uses an IPMSG_BOADCASTOPT command<br>
and an IPMSG_SENDMSG flag should be ON.<br>
Auto-Send packet(absence notice) needs to be added to IPMSG_AUTORETOPT<br>
for ping-pong protection. If either one or another packet is ON, then<br>
confirmation/auto-send packet is not sent back.<br>
<br>
Send Message Sealing needs to be an IPMSG_SECRETOPT packet ON.<br>
In this case, Receive Message sends an IPMSG_READMSG command.<br>
Input the original packet number to the extended area.<br>
<br>
(Additional IPMSG_NOADDLISTOPT)<br>
When receiving an IPMSG_SENDMSG packet from a host that is<br>
not on your Send/Receive list, IPMsg will either confirm a host by<br>
sending an IPMSG_BR_ENTRY command or add a host name to<br>
the Send/Receive list.<br>
However, single-shot Message Send/Receive action needs to be avoided.<br>
Add an IPMSG_NOADDLISTOPT flag to an IPMSG_SENDMSG command.<br>
<br>
(Additional IPMSG_READCHECKOPT from version-8)<br>
When an IPMSG_READMSG command contains an IPMSG_READCHECKOPT flag,<br>
IPMsg process is the same as IPMSG_SENDMSG with an<br>
IPMSG_SENDCHECKOPT flag.<br>
However, Send Message uses an IPMSG_ANSREADMSG command,<br>
not IPMSG_RECVMSG.<br>
<br>
3) Message Send/Receive |encrypted extension (Added in the version-9)<br>
<br>
Use the combination of Public-key(RSA) and common key(RC2/Blowfish).<br>
(Encrypted extension area is used in hex format.)<br>
<br>
(Public key acquisition)Send an IPMSG_GETPUBKEY command to Receive<br>
Message. Receive Message gets an IPMSG_ANSPUBKEY that<br>
means receiving RSA public key from Send Message.<br>
<br>
IPMSG_GETPUBKEY/IPMSG_ANSPUBKEY both require the value which is<br>
encryption capability (Exp. IPMSG_RSA_1024) flag uses "OR" at first<br>
part of extension<br>
<br>
In addition, In IPMSG_ANSPUBKEY, public key written as EE-NNNNNN<br>
E=ExponentAN=method)devide by ':'. and Input the Fdelimiter '-'<br>
between E and N.<br>
<br>
This sequence can be skipped after the 2nd Send/Receive process by<br>
memorizing public key and encrypted data.<br>
<br>
(Encrypted message)After a sender creates a common key that is<br>
supported both sender and receiver, a common key can encrypt a message.<br>
In addition, a receiver's public key encrypts the common key.<br>
<br>
<br>
(Encrypted message transmission) IPMSG_ENCRYPTOPT is used in<br>
IPMSG_SENDMSG. At the first part of extension, input the value which<br>
is 'or' resoult from Convination of public key and common key type .<br>
Then use common key which encrypt with public key devide by ':'.<br>
Then input message which is eccrypted by public key devide by ':'.<br>
If both supports IPMSG_SIGN_XXX, then add ':' and signeture.<br>
<br>
Also, In the method of encode padding, PKCS#1ECB key is used for RSA,<br>
PKCS#5 CBC common key is used for RC2/blowfish.<br>
<br>
Also, The Packet related to Entry manifestation the capability of<br>
ecryption support using  IPMSG_ENCRYPTOPT<br>
<br>
4) Extension with file attachment(Available from version-9)<br>
<br>
An IPMSG_SENDMSG command with an IPMSG_FILEATTACHOPT flag for<br>
File transfer (download permission)notification sends a message<br>
with attachment.<br>
Input '\0' after the message and attachment file data.<br>
<br>
<br>
fileID:filename:size:mtime:fileattr[:extend-attr=val1<br>
[,val2...][:extend-attr2=...]]:\a:fileID...<br>
(size, mtime, and fileattr describe hex format.<br>
If a filename contains ':', please replace with "::".)<br>
<br>
When Receive Message downloads an attachment file, an IPMSG_GETFILEDATA<br>
command requests a data transmission packet to the TCP port that is the same number<br>
as the UDP sending port number. Input packetID:fileID:offset to the extended area.<br>
(Use all hex format.)<br>
File Transfer side receives the request. After recognizing that it's a correct request,<br>
then send the specified data (no format)<br>
<br>
When the data receiving side downloads a hierarchical attachment file,<br>
use an IPMSG_GETDIRFILES command and input a packetID:fileID<br>
to the extended area and send a data transmission request packet.<br>
(all hex format)<br>
<br>
Data sending side sends the following hierarchical data format.<br>
header-size:filename:file-size:fileattr[:extend-attr=val1<br>
[,val2...][:extend-attr2=...]]:contents-data<br>
Next headersize: Next filename...<br>
(All hex format except for filename and contetns-data)<br>
<br>
header-size is from the beginning of header-size to the delimiter ':'<br>
that is before contents-data. extend-attr can be omitted and used multiple<br>
extended attributes. Use '=' for data input.<br>
<br>
When fileattr is IPMSG_FILE_DIR, IPMsg recognizes that it is automatically<br>
in the directory, the next file data is after the directory.<br>
<br>
When fileattr is IPMSG_FILE_RETPARENT, IMPsg recognizes that it returns<br>
to the parent directory. In this case, File name is always "." and the attribute<br>
value is the current directory data.<br>
<br>
Sending process starts from the attachment directly and returns the<br>
IPMSG_FILE_RETPARENT command to the attachment directory.<br>
<br>
Add an IPMSG_FILEATTACHOPT flag for an Entry packet to support the<br>
attachment file.<br>
<br>
5) Other commands<br>
<br>
When acquiring different versions, send an IPMSG_GETINFO command.<br>
Receiving side sends the version information character string to<br>
extended area.<br>
<br>
Send an IPMSG_GETABSENCEINFO command for acquiring an absence message.<br>
Receiving side sends an IPMSG_SENDABSENCEINFO back if the status is absence mode.<br>
If the status is not absence mode, a character string "Not absence mode" will be sent back.<br>
<br>
6) Confirmation/Retry<br>
<br>
If a confirmation packet for IPMSG_SENDMSG or IPMSG_RECVMSG is not delivered<br>
within a specified time, then it will be sent again.<br>
A number of retry actions or interval period is depended on the current condition.<br>
<br>
<br>
4. Other<br>
<br>
1) Linefeed<br>
<br>
Linefeed characters in Send Message is standardized with UNIX type ('0x0a').<br>
Please change if needed.<br>
<br>
2) Delimiter ':'<br>
<br>
':' is used as a delimiter. You can't use this delimiter for user name<br>
and host name.<br>
If the use/host names contain a ':', please replace with another sign,<br>
for an example ';'.<br>
Although using this delimiter isn't problem as yet, I may create an<br>
escape sequence.<br>
<br>
<br>
3) Kanji codes<br>
<br>
SJIS<br>
<br>
<br>
5. Contact e-mail address<br>
<br>
E-Mail shirouzu@h.email.ne.jp<br>
<br>
<br>
Note<br>
See ipmsg.h for command codes.<br>
Please e-mail me your comments and suggestions.<br>
<br>
</pre>