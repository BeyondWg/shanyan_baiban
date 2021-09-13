import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:cl_shanyan_baiban/shanyan.dart';

void main() {
  const MethodChannel channel = MethodChannel('cl_shanyan_baiban');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await ClShanyan.getShanyanVersion(), '42');
  });
}
