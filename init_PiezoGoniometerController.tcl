set workspace [file dirname [file normalize [info script]]]
setws $workspace
cd $workspace

set namePlatform "PiezoGoniometerController"
set nameApp "PiezoGoniometerController_app"
set pathToWorkSpace $workspace
set pathToXsaFile "${pathToWorkSpace}/../PiezoGoniometerController/design_1_wrapper.xsa"
set PlatformSpr "PiezoGoniometerController/platform.spr"
set pathToPlatformSpr [file join $pathToWorkSpace $PlatformSpr]
set domainName "PiezoGoniometerController_Domain"
set PlatformLibDirectory "platform_lib"
set ControllerLibDirectory "controller_lib"
set UtilsLibDirectory "utils_lib"

# Procedures
proc makeDistClean {} {
	global workspace
	puts "Making dist-clean"
	setws -switch "${workspace}/tmp"
	# Eclipse takes some time to disconnect
	after 1000

	foreach {f} [glob -nocomplain fmc_mfe *_system *.bak .Xil .analytics .metadata IDE.log] {
		file delete -force $f
	}

	foreach {f} [glob -nocomplain */_ide */.settings */.project */.cproject */platform.tcl */platform.spr */Debug */Release */*.prj] {
		file delete -force $f
	}

	setws -switch $workspace

	puts "Workspace cleaned\t\[OK\]"
}

proc makeProject {namePlatform pathToXsaFile pathToPlatformSpr pathToWorkSpace domainName} {
	# Platform
	puts "Creating Platform..."
	platform create -name $namePlatform -hw $pathToXsaFile -proc {psu_cortexa53_0} -os {standalone} -arch {64-bit} -fsbl-target {psu_cortexa53_0} -out $pathToWorkSpace
	puts "Writing platform..."
	platform write
	puts "Generating Domain..."
	platform generate -domains 
	puts "Created Platform"
	platform read $pathToPlatformSpr
	puts "Read Platform"
	platform active $namePlatform
	puts "Active Platform"
	platform generate
	
	# Domain
	if {[catch {domain active $domainName}]} {
		domain create -name $domainName -os standalone -proc psu_cortexa53_0 -arch {64-bit}
		puts "Domain Created"
		domain active $domainName
		puts "Domain Active"
	}
	puts "Project created\t\[OK\]"
}

proc makeApp {namePlatform nameApp domainName} {
	domain active $domainName
	# App
	app create -name $nameApp -platform $namePlatform -domain $domainName -template {Empty Application (C++)} -lang {c++}
	puts "App Created"
	app build -name $nameApp
	puts "App Built"
	puts "Application created\t\[OK\]"
}

proc moveCFile {pathToWorkSpace} {
	set sourceDirectory $pathToWorkSpace
	set destFile "PiezoGoniometerController_app/src/main_PiezoGoniometerController.cpp"
	set fileMainName "main_PiezoGoniometerController.cpp"

	# Create the full file paths for the source and destination
	set sourceFile [file join $sourceDirectory $fileMainName]
	set pathToDestinationFile [file join $sourceDirectory $destFile]

	# Check if the source file exists before moving it
	if {[file exists $sourceFile]} {
		# Move the file from the source to the destination
		file copy -force $sourceFile $pathToDestinationFile
		puts "File moved successfully!\t\[OK\]"
	} else {
		puts "Source file does not exist or cannot be accessed."
	}
}

proc moveFilesToSrc {pathToWorkSpace directoryName} {
	# Set the source and destination directories
	set pathToWorkSpace $pathToWorkSpace
	set directoryName $directoryName
	set sourceDirectory [file join $pathToWorkSpace $directoryName]
	set pathToDestinationDirectory "PiezoGoniometerController_app/src"
	set destinationDirectory [file join $pathToWorkSpace $pathToDestinationDirectory]
	puts $destinationDirectory

	# Get a list of all files in the source directory
	set file_list [glob -nocomplain -type f -directory $sourceDirectory *]

	# Iterate over the list of files and copy each one to the destination directory
	foreach file $file_list {
		set fileName [file tail $file]
		set sourcePath [file join $sourceDirectory $fileName]
		set destinationPath [file join $destinationDirectory $fileName]
		file copy -force $sourcePath $destinationPath
		puts "Copied $fileName to $destinationPath \t\[OK\]"
	}
}

# Execute procedures
puts [makeDistClean]
puts [makeProject $namePlatform $pathToXsaFile $pathToPlatformSpr $pathToWorkSpace $domainName]
puts [makeApp $namePlatform $nameApp $domainName]
puts [moveCFile $pathToWorkSpace]
puts [moveFilesToSrc $pathToWorkSpace $PlatformLibDirectory]
puts [moveFilesToSrc $pathToWorkSpace $ControllerLibDirectory]
puts [moveFilesToSrc $pathToWorkSpace $UtilsLibDirectory]

