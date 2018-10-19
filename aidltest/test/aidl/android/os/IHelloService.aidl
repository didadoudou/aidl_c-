// IHelloService.aidl
package android.os;
import sec.ISecResultReceiver;


interface IHelloService {
    void helloWorld();
    void registerReceiver(ISecResultReceiver receiver);
}

