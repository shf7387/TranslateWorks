// OddTools.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>

int main()
{
	FILE *src = fopen("E:\\게임\\jp.co.capcom.gyakusai6jp\\main.4.jp.co.capcom.gyakusai6jp.obb", "r");
	fseek(src, 8, SEEK_SET);

	int count = 0;
	fread(&count, 4, 1, src);
	
	unsigned char *buff = (unsigned char*)malloc(16* count);
	fseek(src, 16, SEEK_SET);
	fread(buff, 16 * count, 1, src);
	
	struct HEADER
	{
		int unno;
		int offset;
		int size;
		int unno2;
	};

	HEADER *header = (HEADER*)buff;

	for (int i = 0; i < count; i++)
	{
		char name[256];
		sprintf(name, "E:\\게임\\jp.co.capcom.gyakusai6jp\\%08X", header[i].unno);
		int off = header[i].offset;
		int size = header[i].size;
		if (size < 1)
		{
			continue;
		}
		unsigned char *buff2 = (unsigned char*)malloc(size);
		memset(buff2, 0, size);
		fseek(src, off, SEEK_SET);
		fread(buff2, size, 1, src);

		FILE *dst = fopen(name, "w");
		fwrite(buff2, size, 1, dst);
		free(buff2);
		fclose(dst);
	}
	free(buff);
	fclose(src);
    return 0;
}