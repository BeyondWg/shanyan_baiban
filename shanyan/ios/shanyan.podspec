#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint shanyan.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'shanyan'
  s.version          = '1.0.1'
  s.summary          = 'A new Flutter plugin.'
  s.description      = <<-DESC
A new Flutter plugin.
                       DESC
  s.homepage         = 'http://flash.253.com/#/index'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files =  'Classes/*'
  s.public_header_files = 'Classes/*.h'
  s.vendored_frameworks = 'Classes/**/*.{framework}'
  s.framework  = "Network"
  s.library   = "c++.1"
  s.dependency 'Flutter'
  s.requires_arc = true
  s.platform = :ios, '8.0'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES',
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386',
        'OTHER_LDFLAGS' => '-ObjC'
    }
end
