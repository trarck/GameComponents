vs2010    打开cocos2d-x下的解决方案。    文件->新键->项目    模板选择Cocos2d-x，再选中Cocos2d-win32 Application。    名称：新的项目的名称.比如"GameComponents"    位置：选中cocos2d-x的根目录。如果选择了添加到解决方案，则会自动选到cocos2d-x目录。    解决方案:选择添加到解决方案。    注意，如果已经有了项目录目录，最好备份下Classes和Resources    删除include和source.新建win32和Classes把proj.win32的头和源文件添加进win32.    Classes目录的文件添加进Classes.    如果有子目录了，则在项目包含路径设置中，添加对子目的支持。IOS方法一:	1.使用create-android-project生成android项目	2.把samples里的HelloCpp里的proj.ios复制到生成的目录。	3.HelloCpp_Prefix.pch==>Prefix.pch,HelloCpp-Info.plist==>Info.plist.	  复制HelloCpp的Resource到生成的目录。	4.打开HelloCpp.xcodeproj，选择Build Setting	  修改 Prefix Header为Prefix.pch，	  info.plist File 为info.plist。	  由于HelloCpp相对于cocos2dx三层目录，而新项目只有二层。所以要修改路径。	  设置cocos2dx子项目录的路径。	  设置Header Search Paths里的相应路径。可以参考附1	  如果Library Search Paths不为空，设置Library Search Paths是的相应路径	  修改Product Name为新的项目名称	5.修改工程名称。	  点击项目名称HelloCpp，会出现输入框，输入新的项目名称。确定重名称其它项。	  修改build schemes.打开Product->Manage Schemes.修改成相应名称。	6.修改info.plist.	  Bundle identifier改为生成android项目时的名称。方法二:	1.使用xode新键一个cocos2dx的项目名称为XX。会同时生成一个同名的目录。并且在子目录中同时会生成XX和XX.xcodeproj	2.把和proj.android在同一目录的XX重命名为proj.ios.	3.把和X.xcodeproj在同一目录的XX下的ios和Resources拷贝到proj.ios目录。一些hello world用的图片拷贝到项目的根目录的Resources中。	4.新建一个ios分组。把之前从ios拷贝到根目录的文件添加到分组。	5.添加项目根目录的Classes和Resources	  在把从Resources拷贝到proj.ios的资源文件添加进Resources目录。	6.删除XX的分组。	7.添加一个libs分组，以便以后使用。	8.把cocos2dx目录下的proj.ios/cocos2dx.xcodeproj的工程文件，拖到当前项目。这样就添加了对cocos2dx的引用。	  添加libcocos2dx库的引用.选中target在summary的 lined frameworks and libraries点+号，有个叫workspace的目录下的libcocos2dx.a。	9.设置Header Search Paths里的相应路径。可以参考附1	  如果Library Search Paths不为空，设置Library Search Paths是的相应路径。	注：关于每三步，可以拷贝ios和Resources二个文件夹到proj.ios目录.把proj.ios/Resources中的一些hello world用的图片拷贝到项目的根目录的Resources中。			附1：	[Header Search Paths]	$(SDKROOT)/usr/include/libxml2	$(SRCROOT)/../../CocosDenshion/include	$(SRCROOT)/../../cocos2dx/kazmath/include	$(SRCROOT)/../../external	$(SRCROOT)/../../cocos2dx	$(SRCROOT)/../../cocos2dx/include	$(SRCROOT)/../../cocos2dx/platform/third_party/ios	$(SRCROOT)/../../cocos2dx/platform/ios	$(SRCROOT)/../../cocos2dx/platform/ios/Simulation"	[Library Search Paths]	$(SRCROOT)/../../cocos2dx/platform/third_party/ios/libraries	[Macros]	USE_FILE32API	TARGET_OS_IPHONE	COCOS2D_DEBUG=1