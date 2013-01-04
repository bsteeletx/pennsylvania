function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcxproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcxproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		var fxtarget = wizard.FindSymbol("TARGET_FRAMEWORK_VERSION");
		if (fxtarget != null && fxtarget != "")
		{
		    fxtarget = fxtarget.split('.', 2);
		    if (fxtarget.length == 2)
			prj.Object.TargetFrameworkVersion = parseInt(fxtarget[0]) * 0x10000 + parseInt(fxtarget[1])
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
	    // Add the folders to your project
	    var group;
        
	    group = proj.Object.AddFilter('Source Files');
        group.Filter = 'cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx';

	    group = proj.Object.AddFilter('Header Files');
	    group.Filter = 'h;hpp;hxx;hm;inl;inc;xsd';

	    group = proj.Object.AddFilter('Resource Files');
	    group.Filter = 'rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav';
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		var config = proj.Object.Configurations('Debug');
		config.CharacterSet = charSetMBCS;
		config.useOfMfc = useOfMfc.useMfcDynamic;

		var CLTool = config.Tools('VCCLCompilerTool');
		// Add compiler settings for Debug build
		CLTool.DebugInformationFormat = debugEnabled; 
		CLTool.DebugInformationFormat = debugOption.debugEditAndContinue;
		CLTool.SuppressStartupBanner = true; 
		CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDebug; 
		CLTool.WarningLevel = warningLevelOption.warningLevel_3; 
		CLTool.Optimization = optimizeOption.optimizeDisabled;
		CLTool.MinimalRebuild = true;
		CLTool.DebugInformationFormat = debugOption.debugEditAndContinue;
		CLTool.AdditionalIncludeDirectories = "C:\\Program Files\\The Game Creators\\AGK\\IDE\\common\\include;"
		CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;_WINDOWS;IDE_VS2008;IDE_VS2010;_CRT_SECURE_NO_WARNINGS;";
		CLTool.UsePrecompiledHeader = pchOption.pchGenerateAuto;	

		var LinkTool = config.Tools('VCLinkerTool');
		// Add linker settings for Debug build
		LinkTool.ProgramDatabaseFile = "$(OutDir)/$(ProjectName).pdb"; 
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes; 
		LinkTool.OutputFile = "$(OutDir)/$(ProjectName).exe";
		LinkTool.SuppressStartupBanner=true;  // nologo
		LinkTool.AdditionalLibraryDirectories = "C:\\Program Files\\The Game Creators\\AGK\\IDE\\platform\\windows\\Lib\\Debug;";
		LinkTool.AdditionalDependencies="AGKWindows.lib OpenGL32.lib winmm.lib";
		LinkTool.SubSystem = subSystemOption.subSystemWindows;

		var MIDLTool = config.Tools('VCMIDLTool');
		MIDLTool.PreprocessorDefinitions = '_DEBUG';
		MIDLTool.MkTypLibCompatible = 'false';
		MIDLTool.ValidateParameters = 'false';

		var ResourceTool = config.Tools('VCResourceCompilerTool');  
		// Add Resource Compiler settings  
		ResourceTool.Culture = enumResourceLangID.rcEnglishUS;  
		ResourceTool.PreprocessorDefinitions = "_DEBUG";  
		ResourceTool.ResourceOutputFileName = "$(IntDir)/$(InputName).res"  

		config = proj.Object.Configurations('Release');
		config.CharacterSet = charSetMBCS;	
		config.useOfMfc = useOfMfc.useMfcDynamic;
		
		var CLTool = config.Tools('VCCLCompilerTool');
		// Add compiler settings for Release build
		CLTool.DebugInformationFormat = debugEnabled; 
		CLTool.DebugInformationFormat = debugOption.debugEnabled;	
		CLTool.SuppressStartupBanner = true; 
		CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreaded; 
		CLTool.WarningLevel = warningLevelOption.warningLevel_3; 
		CLTool.Optimization = optimizeOption.optimizeMaximizeSpeed;
		CLTool.MinimalRebuild = true;
		CLTool.AdditionalIncludeDirectories = "C:\\Program Files\\The Game Creators\\AGK\\IDE\\common\\include;"
		CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;_WINDOWS;IDE_VS2008;IDE_VS2010;_CRT_SECURE_NO_WARNINGS;";
		CLTool.UsePrecompiledHeader = pchOption.pchGenerateAuto;	

		var LinkTool = config.Tools('VCLinkerTool');
		// Add linker settings for Release build
		LinkTool.ProgramDatabaseFile = "$(OutDir)/$(ProjectName).pdb"; 
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes; 
		LinkTool.OutputFile = "$(OutDir)/$(ProjectName).exe";
		LinkTool.SuppressStartupBanner=true;  // nologo
		LinkTool.AdditionalLibraryDirectories = "C:\\Program Files\\The Game Creators\\AGK\\IDE\\platform\\windows\\Lib\\Release;";
		LinkTool.AdditionalDependencies="AGKWindows.lib OpenGL32.lib winmm.lib";
		LinkTool.SubSystem = subSystemOption.subSystemWindows;	
		
		var MIDLTool = config.Tools('VCMIDLTool');
		MIDLTool.PreprocessorDefinitions = 'NDEBUG';
		MIDLTool.MkTypLibCompatible = 'false';
		MIDLTool.ValidateParameters = 'false';
		
		var ResourceTool = config.Tools('VCResourceCompilerTool');
		// Add Resource Compiler settings
		ResourceTool.Culture = enumResourceLangID.rcEnglishUS;
		ResourceTool.PreprocessorDefinitions = "";
		ResourceTool.ResourceOutputFileName = "$(IntDir)/$(InputName).res"
	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	// TODO: specify settings for pre-compiled headers
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		// Set the name of the rendered file based on the template filename
		var strTarget = strName;
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		if (strName == 'readme.txt')
			strTarget = 'ReadMe.txt';

		if (strName == 'CoreForApp.h')
			strTarget =  'CoreForApp.h';		
			
		if (strName == 'Core.cpp')
			strTarget =  'Core.cpp';					

		if (strName == 'Main.h')
			strTarget =  'Main.h';		
			
		if (strName == 'Main.cpp')
			strTarget =  'Main.cpp';					
		
		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}

