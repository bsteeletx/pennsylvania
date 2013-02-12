
#pragma once

class ParentImage
{
public:
	ParentImage(void);
	~ParentImage(void);
    
    unsigned int getImageNumber(const char filename[]);
    bool isDifferent(const char filename[]);
    bool isParentImageSet(void);
    void setImage(const char filename[]);
		
private:
    
    unsigned int pImageNumber[4];
    char fileLoc[4][32];
};


