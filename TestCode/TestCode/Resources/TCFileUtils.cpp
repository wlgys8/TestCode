#include "TCFileUtils.h"
#include "unzip.h"
NS_TC_BEGIN

 bool check_exist_file(const char* filename)
{
	FILE* ftestexist;
	int ret = 1;
	ftestexist = fopen(filename,"rb");
	if (ftestexist==NULL)
		ret = 0;
	else
		fclose(ftestexist);
	return ret;
}

DataStream* TCFileUtils::getFileData(const char* filePath){
	unsigned char * retBuffer = NULL;
	FILE *fp = fopen(filePath, "rb");
	if(fp==NULL){
		 DebugLog("open file failed:%s",filePath);
		 return NULL;
	}
	unsigned long size=0;
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	retBuffer = new unsigned char[size+1];
	size = fread(retBuffer,sizeof(unsigned char), size,fp);
	fclose(fp);
	if(retBuffer==NULL){
		DebugLog("read data from file failed:%s",filePath);
		return NULL;
	}
	retBuffer[size]=0;
	return DataStream::alloc(retBuffer,size);
}
DataStream* TCFileUtils::getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName){

	unsigned char* buffer;
	if(!check_exist_file(pszZipFilePath)){
		DebugLog("file not exist");
		return NULL;
	}
	unzFile zfile= unzOpen(pszZipFilePath);
	if(zfile==NULL){
		DebugLog("open failed");
		return NULL;
	}
	DebugLog("open success!!!!");
	int nRet = unzLocateFile(zfile, pszFileName, 1);
	if(nRet!=UNZ_OK){
		DebugLog("locate file failed:%s",pszFileName);
		return NULL;
	}
	DebugLog("locate file success!!");

	char szFilePathA[260];
	unz_file_info FileInfo;
	nRet = unzGetCurrentFileInfo(zfile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
	if(UNZ_OK != nRet){
		DebugLog("get current file info failed");
		return NULL;
	}
	DebugLog("get current file info success!!");

	nRet = unzOpenCurrentFile(zfile);
	if(UNZ_OK != nRet){
		DebugLog("open current file failed");
		return NULL;
	}
	DebugLog("open current file success!!");


	buffer = new unsigned char[FileInfo.uncompressed_size+1];
	int nSize = 0;
	nSize = unzReadCurrentFile(zfile, buffer, FileInfo.uncompressed_size);
	if(nSize != 0&&nSize != (int)FileInfo.uncompressed_size){
		DebugLog("the file size is wrong");
		return NULL;
	}
	unzCloseCurrentFile(zfile);
	buffer[FileInfo.uncompressed_size]=0;
	return DataStream::alloc(buffer,FileInfo.uncompressed_size);
}

NS_TC_END