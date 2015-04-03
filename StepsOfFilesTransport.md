<pre>
The following steps show how IPMsg transports files/folders:<br>
<br>
Step 1: Sender send a UDP package to tell the receiver that it want<br>
to send some files/folders. The data of the UDP package is formated as:<br>
UDP_DATA = "version:myPackageNumber:userName:hostName:command:"<br>
+ 'NUL' + FILE_INFO + 'NUL'<br>
FILE_INFO = FILE1_INFO + 'BEL' + FILE2_INFO + 'BEL' + ...<br>
FILEn_INFO = "fileNumber:fileName:fileSize:fileLastModifyTime:fileType:"<br>
<br>
Note that fileSize, fileLastModifyTime are hex format. fileType == 1 when it's<br>
is a regular file, fileType == 2 when it's a folder.<br>
command = IPMSG_SENDMSG | IPMSG_FILEATTACHOPT<br>
<br>
Step 2: If the receiver accept one of the files/folders, it will build a TCP<br>
connection to the sender with port 2425.<br>
<br>
Step 3: After the TCP connection was built, the receiver send a TCP package<br>
to the sender. The data of the TCP package is formated as:<br>
TCP_DATA = "version:myPackageNumber:userName:hostName:command:"<br>
+ "senderPackageNumber:fileNumber:offset:"<br>
Note that senderPackageNumber, fileNumber, offset are hex format. If it's<br>
a folder, we don't need "offset:".<br>
command = IPMSG_GETFILEDATA for files or<br>
command = IPMSG_GETDIRFILES for directory.<br>
<br>
Step 4: Now the sender know that the receiver want which file/folder(it got<br>
the senderPackageNumber & fileNumber from step 3). If it's a file,<br>
go to Step 4.1, go to Step 4.2 when it's a folder.<br>
<br>
Step 4.1: Put the file content into a TCP package and send it to the<br>
receiver. Go to Step 5.<br>
<br>
Step 4.2: Send a TCP package that contains data as:<br>
TCP_DATA = "00e:folderName:folderSize:2:"<br>
<br>
Step 4.3: Send a second TCP package which contains all the folders and files<br>
in the folder described at Step 4.2, which is formated as:<br>
FOLDER_CONTENT = SUB_FOLDER1 + SUB_FOLDER2 + .. + SUB_FILE1 + SUB_FILE2 + ..<br>
+ "00a:.:0:3:"<br>
SUB_FOLDERn = "011:folderName:folderSize:2:" + FOLDER_CONTENT<br>
SUB_FILEn = "012:fileName:fileSize:1:fileContent"<br>
<br>
Step 5: Disconnect the TCP connection.<br>
<br>
Step 6: If the receiver want to get the other files, repeat step 2 to 6.<br>
<br>
</pre>