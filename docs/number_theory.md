# Lý thuyết số

## Số nguyên tố

Trong phần này, chúng ta sẽ tìm hiểu về một số thuật toán liên quan đến số nguyên tố.

- Kiểm tra tính nguyên tố của số đã cho
- Kiểm tra tính nguyên tố của các số trong đoạn [a,b]
- Đếm số lượng số nguyên tố trong đoạn [a,b]

**Định nghĩa số nguyên tố**

> Số tự nhiên $n\geq$ 2 chỉ có 2 ước số là 1 và n là số nguyên tố.

### Bài toán 1: Kiểm tra số nguyên tố.

1.  **Thuật toán có độ phức tạp $O(N)$**
    Đơn giản, ta chỉ cần 1 vòng for i từ 2 đến N-1, và xét xem N có chia hết cho i hay không.

    Nếu tồn tại 1 số i là ước của N, thì N không phải số nguyên tố.

2.  **Thuật toán có độ phức tạp $O(\sqrt{N})$**
    Nhận xét rằng 1 số nguyên dương $N \geq 2$ luôn có thể viết lại dưới dạng N = a\*b.

    Không mất tính tổng quát, ta giả sử $a\leq b$, khi đó ta có $a\leq \sqrt{N}$ và $b \geq \sqrt{N} $. Dấu '=' xảy ra khi N là số chính phương.

    Vì $a \leq \sqrt{N}$, nên nếu N không phải là số nguyên tố thì sẽ tồn tại 1 ước số p của N sao cho $p \leq N$. Vậy nên, ta chỉ cần xét các ước số của N từ 1 -> $\sqrt{N}$

    Từ ý tưởng trên. Dưới đây là hàm check số nguyên tố bằng C++.

    ```cpp
     bool check(long long n){
         if (n <= 1) return false;
         long long sqr = sqrt(n);
         for (int i=2;i<=sqr;++i){
             if (n%i==0) return false;
         }
         return true;
     }
    ```

3.  **Thuật toán 6K có độ phức tạp $O(\frac{\sqrt{N}}{6})$**
    Dựa trên thuật toán $O(\sqrt{N})$ ta có thể tối ưu thêm một chút, dựa vào những nhận xét dưới đây

    - Số 2 là số nguyên tố duy nhất là số chẵn $=>$ Mọi số chẵn $> 2 $ không phải là số nguyên tố. Nói cách khác, ta chỉ cần xét các số lẻ trong đoạn [2,$\sqrt{N}$]

    * Tương tự, nếu $N > 3$ thì ta chỉ cần xét các số không chia hết cho 3 trong đoạn [3,$\sqrt{N}$]

    Từ 2 nhận xét trên, ta có thể rút ra được một kết luận rằng.

    > Mọi số $N\geq5$ nếu là số nguyên tố, thì N có dạng 6k-1 hoặc 6k+1. Với k là một số nguyên dương. (Lưu ý, điều ngược lại không đúng).

    Từ kết luận trên. Dưới đây là hàm check số nguyên tố bằng C++.

    ```cpp
     bool check(long long n){
         if (n <= 1) return false;
         if (n==2 || n == 3) return true;
         if (n%2==0 || n%3==0)   return false;
         long long sqr = sqrt(n);
         for (int i=6;i<=sqr;i+=5){
             if (n%i==0 || n%(i+2)==0) return false;
         }
         return true;
     }
    ```

    Tất nhiên, ta có thể tăng số lượng số nguyên tố được dùng để xét trước nhằm tối ưu thuật toán hơn. Tuy nhiên, việc cài đặt thuật toán sẽ rất phức tạp và không đáng. Ngoài ra, có một số tài liệu đã chứng minh rằng cho dù sử dụng $6.10^5$ số nguyên tố đầu tiên. Thì độ phức tạp đạt được chỉ khoảng $O(\frac{\sqrt{N}}{30})$. <br>
    Thuật toán 6K đủ nhanh để kiểm tra khi giới hạn $N\leq 10^{16}$. Với những bài toán có giới hạn lớn hơn, ví dụ như $N\leq 10^{18}$. Ta cần sử dụng đến phương pháp xác suất. Tức là dự đoán xem N có phải là số nguyên tố hay không (Tất nhiên sẽ có trường hợp dự đoán sai).

4.  **Thuật toán phép thử Fermat nhỏ.**
    Theo định lý Fermat nhỏ. Nếu $p$ là một số nguyên tố thì với mọi số nguyên $a$ thỏa mãn $gcd(a,b)=1$, ta có
    $$a^{p-1} \equiv 1 \pmod{n}$$

    Từ định lý Fermat nhỏ, ta có ý tưởng kiểm tra tính nguyên tố của một số nguyên dương $n \geq 2$ như sau.

    - Xét số nguyên $a \in [2,n-1]$, nếu $a^{n-1} \not\equiv 1 \pmod{n}$, thì **chắc chắn** rằng n không phải số nguyên tố
    - Ngược lại, nếu $a \in [2,n-1]$, nếu $a^{n-1} \equiv 1 \pmod{n}$, thì n **có thể** là số nguyên tố.
      **Ví dụ**
      Trường hợp n không phải số nguyên tố nhưng $a^{n-1} \equiv 1 \pmod{n}$
      Chọn n = 15, a = 4 thì $4^{14} \equiv 1 \pmod{15}$ nhưng n = 15 thực chất không phải là số nguyên tố. Trong trường hợp này, n được gọi là **số giả nguyên tố**.<br>
      Về mặt lý thuyết. Nếu ta kiểm tra đẳng thức Fermat với mọi số $a \in [2,n-1]$, ta có thể kết luận chắc chắn về tính nguyên tố của n. Tuy nhiên, nếu làm như vậy thì độ phức tạp sẽ lớn hơn cả thuật toán ngây thơ. Do đó, ta chỉ kiểm tra đẳng thức Fermat với một vài số $a$ được lấy ngẫu nhiên trong đoạn $[2,n-1]$.
      Trong các bài toán lập trình thi đấu, phép thử vẫn đạt được độ chính xác đủ tốt.<br>
      Dựa vào ý tưởng trên, dưới đây là cách cài đặt bằng C++.<br>
      Cách cài đặt dưới đây sẽ xử lý với giới hạn $n \leq 10^{18}$. Do vậy sẽ cần sử dụng **hàm lũy thừa nhị phân (binary power)** để tính $a^{n-1} \% n$ và **hàm tích nhị phân (binary multiplication)** để tính $(a*a)\%n$ trong thuật toán **binary power**

      ```cpp
        long long binaryMul(long long a,long long b,long long n){
            a = a % n;
            long long res = 0;
            while (b>0){
                if (b%2!=0) res = (res+a)%n;
                a = (a+a)%n;
                b /= 2;
            }
            return res;
        }
        long long binaryPow(long long a,long long k,long long n){
            a = a % n;
            long long res = 1;
            while (k > 0){
                if (k%2!=0) res = binaryMul(res,a,n);
                k = binaryMul(a,a,n);
                k/=2;
            }
            return res;
        }
        bool check(long long n){
            if (n<=1)   return false;
            if (n==2||n==3||n==5)   return true;
            if (n%2==0||n%3==0||n%5==0) return false;

            int times = 10;
            for (int i=1;i<=times;++i){
                long long a = rand() % (n-2) + 2;
                if (binaryPower(a,n-1,n) != 1) return false;
            }
            return true;
        }
      ```

      Độ phức tạp của thuật toán check trên là $O(Times*log^2(n))$
      **Chú ý:** Do không có tính chính xác tuyệt đối nên phép thử Fermat không phải là một thuật toán.

      Mặc dù có tốc độ cao và dễ cài đặt, nhưng vẫn có những trường hợp xác suất thất bại là rất cao. Ví dụ xét số $n = 561 = 3 \times 11 \times 17$. Số này có tính chất **với mọi số nguyên a mà $gcd(a,n) = 1$ thì $a^{n-1} \equiv 1 \pmod{n}$**. Do đó, nếu trong quá trình thử, không chọn được số $a$ chia hết cho 3, 11 hoặc 17 thì phép thử sẽ cho kết quả sai. <br>

      Các số có tính chất trên được gọi là **Số Carmichael**.
      Trong lập trình thi đấu, phép thử Fermat sẽ đáng tin cậy nếu test được sinh ngẫu nhiên, vì xác suất gặp số Carmichael rất thấp. Tuy nhiên, nếu test cố tình chọn số Carmichael thì phép thử sẽ không còn đáng tin cậy. Rất may là có những phép thử hiệu quả và đáng tin cậy hơn phép thử Fermat. Trong phần tiếp theo ta sẽ tìm hiểu về **thuật toán Rabin-Miller**.
