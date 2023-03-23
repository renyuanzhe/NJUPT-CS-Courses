#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <winnt.h>
#include <imagehlp.h>
#pragma comment(lib,"IMAGEHLP")

using namespace std;

PIMAGE_DOS_HEADER pDH = NULL;
PIMAGE_NT_HEADERS pNtH = NULL;
PIMAGE_FILE_HEADER pFH = NULL;
PIMAGE_OPTIONAL_HEADER pOH= NULL;
PIMAGE_SECTION_HEADER pSH = NULL;
PIMAGE_IMPORT_DESCRIPTOR pIMT = NULL;
LPVOID  imageBase = NULL;

//E://Hill.exe
//载入文件
BOOL loadPE(LPSTR fileName)
{
    HANDLE hFile;
    HANDLE hMapping;

    //打开文件，返回句柄
    hFile=CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (!hFile)
    {
        cout << "文件加载错误..." << endl;
        return FALSE;
    }
    //创建内存映射对象，将PE文件装载到内存
    hMapping = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,GetFileSize(hFile,NULL),NULL);
    if(!hMapping)
    {
        cout << "文件加载错误..." << endl;
        CloseHandle(hFile);
        return FALSE;
    }
    imageBase = MapViewOfFile(hMapping,FILE_MAP_READ,0,0,0);
    if(!imageBase)
    {
        CloseHandle(hMapping);
        CloseHandle(hFile);
        cout << "文件加载错误..." << endl;
        return FALSE;
    }
    //printf("ImageBase : %x\n",imageBase);
    return TRUE;
}

//判断是否PE文件
BOOL isPE()
{
    pDH=(PIMAGE_DOS_HEADER)imageBase;
    pNtH=(PIMAGE_NT_HEADERS32)((DWORD)pDH+pDH->e_lfanew);//pNtH PE文件头标志

    //判断文件第一个字段是否是MZ，即5A4D
    printf("e_magic : %x\n",pDH->e_magic);
    if(pDH->e_magic!=IMAGE_DOS_SIGNATURE)
    {
        cout << "格式错误，请选择PE格式的文件..." << endl;
        return FALSE;
    }
    //即使是MZ，为防止误判断，比较Signature和IMAGE_NT_SIGNATURE，应该相等且为4550
    printf("Signature : %x\n",pNtH->Signature);
    printf("IMAGE_NT_SIGNATURE : %x\n",IMAGE_NT_SIGNATURE);
    if (pNtH->Signature != IMAGE_NT_SIGNATURE)
    {
        cout << "格式错误，请选择PE格式的文件..." << endl;
        return FALSE;
    }
    cout << "已确认PE文件格式正确..." << endl;

    return TRUE;
}

//读IMAGE_FILE_HEADER结构体中内容
void getFileHeader()
{
    pFH=&(pNtH->FileHeader);
    printf("机器CPU类型 : ");
    if(pFH->Machine == 0x014c)
        printf("Intel i386");
    else if(pFH->Machine == 0x0162)
        printf("MIPS R3000");
    else if(pFH->Machine == 0x0166)
        printf("MIPS R4000");
    else if(pFH->Machine == 0x0184)
        printf("Alpha AXP");
    else printf("Power PC");
    printf("( %x )\n",pFH->Machine);
    printf("编译时间 : ");
    //printf(ctime((time_t*)&pFH->TimeDateStamp));
    printf("(%x)\n",(time_t*)&pFH->TimeDateStamp);

    printf("类型 : ");
    if(pFH->Characteristics == 0x010f)
        printf("普通EXE文件");
    if(pFH->Characteristics == 0x0210)
        printf("DLL文件");
	else printf("其他");
    printf("( %x )\n",pFH->Characteristics);

    //判断文件32位还是64，size依赖于文件类型
    printf("类型(32 or 64) : ");
    if(pFH->SizeOfOptionalHeader == 0x00E0)
        printf("32位");
    if(pFH->SizeOfOptionalHeader == 0x00F0)
        printf("64位");
    printf("( %x )\n",pFH->SizeOfOptionalHeader);

    printf("Section数目 : %x\n", pFH->NumberOfSections);
    //是否存在COFF符号表，偏移位置
	printf("是否存在COFF符号表 : ");
	if(pFH->PointerToSymbolTable == 0)
        printf("COFF不存在");
    else
        printf("COFF存在");
    printf("( %x )\n",pFH->PointerToSymbolTable);
	printf("符号表大小 : %x\n", pFH->NumberOfSymbols);
}

//读IMAGE_OPTIONAL_HEADER结构体中类容
void getOptionalHeader()
{
    pOH = &(pNtH ->OptionalHeader);
    //
    printf("ROM or EXECUTABLE : ");
    if(pOH->Magic == 0x0107)
        printf("ROM");
    if(pOH->Magic == 0x010B)
        printf("EXECUTABLE");
	if(pOH->Magic == 0x020b)
        printf("PE32+");
    printf("( %x )\n",pOH->Magic);
    printf("用户界面类型 ：");
    if(pOH->Subsystem == 0)printf("未知\n");
    if(pOH->Subsystem == 1)printf("不需要子系统（可能是驱动）\n");
    if(pOH->Subsystem == 2)printf("GUI图形界面\n");
    if(pOH->Subsystem == 3)printf("CUI命令行界面\n");
    if(pOH->Subsystem == 5)printf("OS/2字符子系统\n");
    if(pOH->Subsystem == 7)printf("POSIX字符子系统\n");
    if(pOH->Subsystem == 8)printf("保留\n");
    if(pOH->Subsystem == 9)printf("WINDOWS CE界面\n");

    printf("链接程序主版本号 : %x\n",pOH->MajorLinkerVersion);
    //已初始化数据块大小，编译时所构成的块的大小（不包括代码段）
    printf("已初始化数据块大小 : %x\n",pOH->SizeOfInitializedData);
    //未初始化数据块，程序运行时没有指定值
    printf("未初始化数据块 : %x\n",pOH->SizeOfUninitializedData);
    printf("映象校验和 ：%x\n",pOH->CheckSum);

    printf("映象装入内存后总尺寸 : %x\n",pOH->SizeOfImage);
    printf("MS头，PE头，SECTION表大小 ： %x\n",pOH->SizeOfHeaders);
    printf(".text大小 : %x\n",pOH->SizeOfCode);

    printf("代码段起始RVA : %x\n",pOH->BaseOfCode);
    printf("数据段起始RVA : %x\n",pOH->BaseOfData);
    //程序执行入口RVA，指向运行时库代码，再由其指向main
    printf("程序执行入口RVA : %x\n",pOH->AddressOfEntryPoint);
    printf("基址 : %x\n\n",pOH->ImageBase);
    //装入内存后区块对齐大小,必须从磁盘扇区开始
    printf("装入内存后区块对齐大小 ： %x\n",pOH->FileAlignment);
    printf("磁盘上区块对齐大小： %x\n",pOH->SectionAlignment);
    printf("一开始被委派给堆栈的内存大小 : %x\n",pOH->SizeOfStackCommit);
    printf("一开始被委派给堆的内存大小 : %x\n",pOH->SizeOfHeapCommit);
    printf("为线程堆栈保留的 : %x\n",pOH->SizeOfHeapReserve);
    printf("为线程堆保留的 : %x\n",pOH->SizeOfHeapReserve);
}

//读数据目录表
void getDataDirectory()
{
    for(int i = 0;i < 16;i++)//数据目录表共16项，遍历
    {
        char* item = "";
        if(pOH->DataDirectory[i].VirtualAddress == 0&&pOH->DataDirectory[i].Size == 0)
            continue;
        if(i == 0)item = "Export Table";
        if(i == 1)item = "Import Table";
        if(i == 2)item = "Resource Table";
        if(i == 3)item = "Exception Table";
        if(i == 4)item = "Security Table";
        if(i == 5)item = "Base Relocation";
        if(i == 6)item = "Debug Table";
        if(i == 7)item = "Copy Right";
        if(i == 8)item = "Global ptr";
        if(i == 9)item = "TLS";
        if(i == 10)item = "Load configuration";
        if(i == 11)item = "Bound Import";
        if(i == 12)item = "Import Address Table";
        if(i == 13)item = "Delay Import";
        if(i == 14)item = "COM Descriptor";
        if(i == 15)item = "保留";

        printf("%s(数据目录表第%d项)\n",item,i+1);
        printf("VirtualAddress，%x\n",pOH->DataDirectory[i].VirtualAddress);
        printf("Size，%x\n",pOH->DataDirectory[i].Size);
    }
}

//读区块信息
void getSectionTable()
{
    pSH = IMAGE_FIRST_SECTION(pNtH);
    for(int i = 0;i < pFH->NumberOfSections;i++)
    {
        printf("%s ",pSH->Name);
		//Characteristics是通过求或得到，按位与可得知是否包含属性
        if(IMAGE_SCN_CNT_CODE&pSH->Characteristics)cout<<"包含可执行代码,";
		if(IMAGE_SCN_MEM_EXECUTE&pSH->Characteristics)cout<<"可执行,";
		if(IMAGE_SCN_CNT_INITIALIZED_DATA&pSH->Characteristics)cout<<"包含已初始化数据,";
		if(IMAGE_SCN_CNT_UNINITIALIZED_DATA&pSH->Characteristics)cout<<"包含未初始化数据,";
		if(IMAGE_SCN_MEM_DISCARDABLE&pSH->Characteristics)cout<<"可被丢弃,";
		if(IMAGE_SCN_MEM_SHARED&pSH->Characteristics)cout<<"共享块,";
		if(IMAGE_SCN_MEM_READ&pSH->Characteristics)cout<<"可读,";
        if(IMAGE_SCN_MEM_WRITE&pSH->Characteristics)cout<<"可写,";
		printf("(%x)\n",pSH->Characteristics);
		//这里SIZE没读出来
		printf("该块装载到内存中的RVA %x\n",pSH->VirtualAddress);
        printf("该块在磁盘中大小 %x\n",pSH->SizeOfRawData);
        printf("该块在磁盘中偏移 %x\n",pSH->PointerToRawData);
        ++pSH;
    }
}
//返回扩展PE头中DataDirectory数据目录的真实地址
LPVOID getDirectoryEntryToData(USHORT DirectoryEntry)
{

	LPVOID pDirData=NULL;
	DWORD dwDataStartRVA = 0;

	//数据目录表，1是导入，指向IID，0是导出，指向IED
    dwDataStartRVA=pOH->DataDirectory[DirectoryEntry].VirtualAddress;
	//printf("%x %x\n",imageBase,dwDataStartRVA);
    if(!dwDataStartRVA)
        return NULL;
	//已知RVA，得到VA
	pDirData = ImageRvaToVa(pNtH,imageBase,dwDataStartRVA,NULL);//pNtH=(PIMAGE_NT_HEADERS32)((DWORD)pDH+pDH->e_lfanew);
    if(!pDirData)
		return NULL;
   	return  pDirData;
}

//读DLL对应导入函数
void getImportFuction(int index)
{
    DWORD dwThunk,*pdwThunk=NULL,*pdwRVA=NULL;
	PIMAGE_IMPORT_DESCRIPTOR pIFT = NULL;
	PIMAGE_IMPORT_BY_NAME pIBN = NULL;
	//当前IID索引
    pIFT=&pIMT[index];
	//指向INT，如果不存在，那么指向IAT
    dwThunk=((DWORD)((PIMAGE_IMPORT_DESCRIPTOR)pIMT->OriginalFirstThunk?                      \
         (PIMAGE_IMPORT_DESCRIPTOR)pIMT->OriginalFirstThunk:(PIMAGE_IMPORT_DESCRIPTOR)pIMT->FirstThunk \
          ));

	//RVA
	pdwRVA=(DWORD *)dwThunk;
	//VA
	pdwThunk=(DWORD*)ImageRvaToVa(pNtH,imageBase,dwThunk,NULL);
   	if(!pdwThunk)
		    return;
    while(*pdwThunk)
    {
		printf("%x ",(DWORD)pdwRVA);
		printf("%x ", (DWORD)(*pdwThunk));
		//如果高位为1，函数以序号方式输入
		if (HIWORD(*pdwThunk) == 0x8000)
		{
			printf("%x ",IMAGE_ORDINAL32(*pdwThunk));
		}
		//否则字符串类型输入，此时是指向IMAGE_IMPORT_BY_NAME的RVA
		else
		{
			pIBN =(PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(pNtH,imageBase,(DWORD)(*pdwThunk),NULL);
			if(pIBN)
			{
				//本函数在其所驻留DLL中的序号，可能被设0
				printf("%x ",pIBN->Hint);
				string temp = (char*)pIBN->Name;
				printf("%s\n",temp.c_str());
			}
			else
			{
				printf("%x ",(DWORD)(*pdwThunk));
			}
		}
		++pdwRVA;
		++pdwThunk;
	}
	cout << "--------------------------------" << endl;
}

//读导入DLL
void getImportTable()
{
    int i = 0;
	//得到IID数组（描述DLL文件）的VA
    pIMT = (PIMAGE_IMPORT_DESCRIPTOR)getDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IMPORT);
	if(!pIMT)
	{
		printf("导入表为空\n");
	}
	else
	{
		while(pIMT->FirstThunk)//没有项数字段，但最后一个单元为NULL
		{
			//NAME是DLL名字的指针
			printf("%s %x\n",ImageRvaToVa(pNtH,imageBase,pIMT->Name,NULL),pIMT->Name);
			cout << "------------getImportFuction--------------------" << endl;
			//得到该DLL导入函数
			getImportFuction(i);
			//指向下一个DLL
			++pIMT;
			i++;
		}
	}
}

//读导出函数
void getExportTable()
{
	PDWORD pdwRva, pdwName;
	PWORD pMap;
	string funcName;
	PIMAGE_EXPORT_DIRECTORY pEXT = NULL;
	//得到IED
	pEXT = (PIMAGE_EXPORT_DIRECTORY)getDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_EXPORT);

	if(!pEXT)
	{
		printf("导出表为空\n");
	}
	else
	{
		//EAT函数表
		pdwRva = (PDWORD)ImageRvaToVa(pNtH,imageBase,pEXT->AddressOfFunctions,NULL);
		//ENT名称表
		pdwName = (PDWORD)ImageRvaToVa(pNtH,imageBase,pEXT->AddressOfNames,NULL);
		//对应序号表
		pMap = (PWORD)ImageRvaToVa(pNtH,imageBase,pEXT->AddressOfNameOrdinals,NULL);
		printf("共%d导出函数\n",pEXT->NumberOfFunctions);

		if(!pdwRva)
			return;
		//循环导出函数地址
		for(int i = 0;i < pEXT->NumberOfFunctions;i++)
		{
			for(int j = 0;j < pEXT->NumberOfNames;j++)
			{
				if(i == pMap[j])
				{
					//名称表和序号表是对应的
					funcName = (char*)ImageRvaToVa(pNtH,imageBase,pdwName[j],NULL);
					break;
				}
			}
			//地址正确对应名称
			printf("%x ", pEXT->Base+i);
			printf("%x ", (*pdwRva));
			printf("%s\n",funcName.c_str());
			++pdwRva;
		}
	}
}

void getResource()
{
    PIMAGE_RESOURCE_DIRECTORY pRD = NULL;
    pRD = (PIMAGE_RESOURCE_DIRECTORY)getDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_RESOURCE);
    if(!pRD)
	{
		printf("资源为空\n");
		return;
	}
    printf("用户自定义资源数 %x\n典型资源数（如对话框）%x \n",pRD->NumberOfIdEntries,pRD->NumberOfNamedEntries);
}



int main()
{
	char fileName[30];
	cout << "\n请输入exe文件的绝对路径 : ";
	cin.getline(fileName,50);
    cout << "\n您输入参数为 : "<< fileName << endl;

	//加载文件
    int a = loadPE(fileName);
    if(!a)
        return 1;
    cout << "文件 " << fileName << " 读取成功...\n" << endl;
    cout << "--------------------------------" << endl;

   

    //是否PE类型文件
    int flag = isPE();
    if(!flag)
    {
        return 1;
    }
   
	
	cout << fileName <<"分析结果包括其PE文件头(IMAGE_FILE_HEADER，IMAGE_OPTIONAL_HEADER，数据目录表)，" <<
		"区块信息以及导入导出表信息\n" << endl;

    //读IMAGE_FILE_HEADER结构体中内容
    cout << "-------IMAGE_FILE_HEADER--------" << endl;
    getFileHeader();
    cout << "" << endl;

    //读IMAGE_OPTIONAL_HEADER结构体中内容
    cout << "-------IMAGE_OPTIONAL_HEADER--------" << endl;
    getOptionalHeader();
    cout << "" << endl;

    //读数据目录表
    cout << "DATA_DIRECTORY（非0项）" << endl;
    getDataDirectory();
    cout << "" << endl;

    //读区块表信息
    cout << "-------IMAGE_SECTION_HEADER---------" << endl;
    getSectionTable();
    cout << "" << endl;

    //读资源
    cout << "--------------RESOURCE--------------" << endl;
    getResource();
    cout << "" << endl;

    //读导入表
    cout << "------------IMPORT_TABLE------------" << endl;
    getImportTable();
    cout << "" << endl;

	//读导出表
    cout << "------------EXPORT_TABLE------------" << endl;
    getExportTable();
    cout << "------------------------------------\n" << endl;

	//分析完成
	freopen( "CON", "w", stdout ); //重定向输出到控制台
	cout << ""<<fileName<<"分析完成..." << endl;
	system("pause"); 
    return 0;
}