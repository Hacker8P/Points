function Hash(Text) {
    async function SHA256(Message) {
        // encode as UTF-8
        const msgBuffer = new TextEncoder().encode(Message);

        // hash the message
        const hashBuffer = await crypto.subtle.digest('SHA-256', msgBuffer);

        // convert ArrayBuffer to Array
        const hashArray = Array.from(new Uint8Array(hashBuffer));

        // convert bytes to hex string                  
        const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
        return hashHex;
    }

    return SHA256(Text)
}

function Send() {
    var Credentials = [document.getElementById("Email"), document.getElementById("Password")]

    Credentials = {Email: Credentials[0].value, Password: Credentials[1].value}

    console.log(Credentials)

    console.log(CryptoJS.SHA256("Ciao"))

    fetch("Server/Login", {
        method: "POST",
        body: JSON.stringify(Credentials)
    })
}

function Callbacks() {
    var SubmitButton = document.getElementById("SignIn")

    SubmitButton.onclick = () => {Send()}
}

function main() {
    Callbacks()

    return 0;
}

main();